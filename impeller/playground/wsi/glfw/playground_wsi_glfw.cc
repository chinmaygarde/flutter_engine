// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/wsi/glfw/playground_wsi_glfw.h"

#include <mutex>

#define GLFW_INCLUDE_NONE
#include "third_party/glfw/include/GLFW/glfw3.h"

#include "flutter/fml/logging.h"

namespace impeller {

struct PlaygroundWSIGLFW::GLFWInitializer {
  GLFWInitializer() {
    // This guard is a hack to work around a problem where glfwCreateWindow
    // hangs when opening a second window after GLFW has been reinitialized (for
    // example, when flipping through multiple playground tests).
    //
    // Explanation:
    //  * glfwCreateWindow calls [NSApp run], which begins running the event
    //    loop on the current thread.
    //  * GLFW then immediately stops the loop when
    //    applicationDidFinishLaunching is fired.
    //  * applicationDidFinishLaunching is only ever fired once during the
    //    application's lifetime, so subsequent calls to [NSApp run] will always
    //    hang with this setup.
    //  * glfwInit resets the flag that guards against [NSApp run] being
    //    called a second time, which causes the subsequent `glfwCreateWindow`
    //    to hang indefinitely in the event loop, because
    //    applicationDidFinishLaunching is never fired.
    static std::once_flag sOnceInitializer;
    std::call_once(sOnceInitializer, []() {
      ::glfwSetErrorCallback([](int code, const char* description) {
        FML_LOG(ERROR) << "GLFW Error '" << description << "'  (" << code
                       << ").";
      });
      FML_CHECK(::glfwInit() == GLFW_TRUE);
    });
  }
};

PlaygroundWSIGLFW::PlaygroundWSIGLFW()
    : glfw_initializer_(std::make_unique<GLFWInitializer>()) {}

PlaygroundWSIGLFW::~PlaygroundWSIGLFW() = default;

// |PlaygroundWSI|
std::unique_ptr<PlaygroundWindow> PlaygroundWSIGLFW::CreateWindow(
    PlaygroundWSIBackend backend) {}

}  // namespace impeller
