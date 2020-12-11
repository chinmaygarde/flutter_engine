// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define FML_USED_ON_EMBEDDER

#include "flutter/fml/thread.h"

#include <unistd.h>

#include <memory>
#include <string>

#include "flutter/fml/build_config.h"
#include "flutter/fml/message_loop.h"
#include "flutter/fml/synchronization/waitable_event.h"

#if defined(OS_WIN)
#include <windows.h>
#elif defined(OS_FUCHSIA)
#include <lib/zx/thread.h>
#else
#include <pthread.h>
#endif

namespace fml {

typedef void (*ThreadEntry)(Thread*);

static size_t NextPageSizeMultiple(size_t size) {
  const size_t page_size = sysconf(_SC_PAGESIZE);
  FML_CHECK(page_size != 0);

  size = std::max<size_t>(size, page_size);

  size_t rem = size % page_size;

  if (rem == 0) {
    return size;
  }

  return size + page_size - rem;
}

static bool CreateThread(pthread_t* thread,
                         ThreadEntry main,
                         Thread* argument,
                         size_t stack_size) {
  pthread_attr_t thread_attributes;

  if (pthread_attr_init(&thread_attributes) != 0) {
    return false;
  }

  stack_size = std::max<size_t>(NextPageSizeMultiple(PTHREAD_STACK_MIN),
                                NextPageSizeMultiple(stack_size));

  if (pthread_attr_setstacksize(&thread_attributes, stack_size) != 0) {
    return false;
  }

  auto result =
      pthread_create(thread, &thread_attributes,
                     reinterpret_cast<void* (*)(void*)>(main), argument);

  pthread_attr_destroy(&thread_attributes);

  return result == 0;
}

Thread::Thread(const std::string& name) : joined_(false) {
  FML_CHECK(CreateThread(
      &thread_, [](Thread* thread) { thread->Main(); }, this, 1 << 20));
  latch_.Wait();
}

Thread::~Thread() {
  Join();
}

void Thread::Main() {
  fml::MessageLoop::EnsureInitializedForCurrentThread();
  auto& loop = MessageLoop::GetCurrent();
  task_runner_ = loop.GetTaskRunner();
  latch_.Signal();
  loop.Run();
}

fml::RefPtr<fml::TaskRunner> Thread::GetTaskRunner() const {
  return task_runner_;
}

void Thread::Join() {
  if (joined_) {
    return;
  }
  joined_ = true;
  task_runner_->PostTask([]() { MessageLoop::GetCurrent().Terminate(); });
  FML_CHECK(pthread_join(thread_, nullptr) == 0);
}

#if defined(OS_WIN)
// The information on how to set the thread name comes from
// a MSDN article: http://msdn2.microsoft.com/en-us/library/xcb2z8hs.aspx
const DWORD kVCThreadNameException = 0x406D1388;
typedef struct tagTHREADNAME_INFO {
  DWORD dwType;      // Must be 0x1000.
  LPCSTR szName;     // Pointer to name (in user addr space).
  DWORD dwThreadID;  // Thread ID (-1=caller thread).
  DWORD dwFlags;     // Reserved for future use, must be zero.
} THREADNAME_INFO;
#endif

void Thread::SetCurrentThreadName(const std::string& name) {
  if (name == "") {
    return;
  }
#if defined(OS_MACOSX)
  pthread_setname_np(name.c_str());
#elif defined(OS_LINUX) || defined(OS_ANDROID)
  pthread_setname_np(pthread_self(), name.c_str());
#elif defined(OS_WIN)
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = name.c_str();
  info.dwThreadID = GetCurrentThreadId();
  info.dwFlags = 0;
  __try {
    RaiseException(kVCThreadNameException, 0, sizeof(info) / sizeof(DWORD),
                   reinterpret_cast<DWORD_PTR*>(&info));
  } __except (EXCEPTION_CONTINUE_EXECUTION) {
  }
#elif defined(OS_FUCHSIA)
  zx::thread::self()->set_property(ZX_PROP_NAME, name.c_str(), name.size());
#else
  FML_DLOG(INFO) << "Could not set the thread name to '" << name
                 << "' on this platform.";
#endif
}

}  // namespace fml
