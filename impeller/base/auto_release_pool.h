// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "flutter/fml/build_config.h"
#include "flutter/fml/macros.h"

#if FML_OS_MACOSX
#include <objc/message.h>
#include <objc/runtime.h>
#endif  // FML_OS_MACOSX

namespace impeller {

class AutoReleasePool {
 public:
  AutoReleasePool() {
#if FML_OS_MACOSX
    pool_ = reinterpret_cast<msg_send>(objc_msgSend)(
        objc_getClass("NSAutoreleasePool"), sel_getUid("new"));
#endif  // FML_OS_MACOSX
  }

  ~AutoReleasePool() {
#if FML_OS_MACOSX
    reinterpret_cast<msg_send>(objc_msgSend)(pool_, sel_getUid("drain"));
#endif  // FML_OS_MACOSX
  }

 private:
#if FML_OS_MACOSX
  typedef id (*msg_send)(void*, SEL);
  id pool_;
#endif  // FML_OS_MACOSX

  FML_DISALLOW_COPY_AND_ASSIGN(AutoReleasePool);
};

}  // namespace impeller
