// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/wsi/glfw/playground_window_glfw.h"

#include <optional>

#include "impeller/base/validation.h"

namespace impeller {

static void PlaygroundKeyCallback(GLFWwindow* window,
                                  int key,
                                  int scancode,
                                  int action,
                                  int mods) {
  if ((key == GLFW_KEY_ESCAPE) && action == GLFW_RELEASE) {
    if (mods & (GLFW_MOD_CONTROL | GLFW_MOD_SUPER | GLFW_MOD_SHIFT)) {
      gShouldOpenNewPlaygrounds = false;
    }
    ::glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

static std::optional<PlaygroundKeyAction> ToPlaygroundKeyAction(int action) {
  switch (action) {
    case GLFW_PRESS:
      return PlaygroundKeyAction::kPress;
    case GLFW_RELEASE:
      return PlaygroundKeyAction::kRelease;
    case GLFW_REPEAT:
      return PlaygroundKeyAction::kRepeat;
  }
  return std::nullopt;
}

static std::optional<PlaygroundKeyModifier> ToPlaygroundKeyModifier(
    int modifier) {
  switch (modifier) {
    case GLFW_MOD_SHIFT:
      return PlaygroundKeyModifier::kShift;
    case GLFW_MOD_CONTROL:
      return PlaygroundKeyModifier::kControl;
    case GLFW_MOD_ALT:
      return PlaygroundKeyModifier::kAlt;
    case GLFW_MOD_SUPER:
      return PlaygroundKeyModifier::kSuper;
    case GLFW_MOD_CAPS_LOCK:
      return PlaygroundKeyModifier::kCapsLock;
    case GLFW_MOD_NUM_LOCK:
      return PlaygroundKeyModifier::kNumLock;
  }
  return std::nullopt;
}

static std::optional<PlaygroundKeyCode> ToPlaygroundKeyCode(int keycode) {
  switch (keycode) {
    case GLFW_KEY_SPACE:
      return PlaygroundKeyCode::kSpace;
    case GLFW_KEY_APOSTROPHE:
      return PlaygroundKeyCode::kApostrophe;
    case GLFW_KEY_COMMA:
      return PlaygroundKeyCode::kComma;
    case GLFW_KEY_MINUS:
      return PlaygroundKeyCode::kMinus;
    case GLFW_KEY_PERIOD:
      return PlaygroundKeyCode::kPeriod;
    case GLFW_KEY_SLASH:
      return PlaygroundKeyCode::kSlash;
    case GLFW_KEY_0:
      return PlaygroundKeyCode::k0;
    case GLFW_KEY_1:
      return PlaygroundKeyCode::k1;
    case GLFW_KEY_2:
      return PlaygroundKeyCode::k2;
    case GLFW_KEY_3:
      return PlaygroundKeyCode::k3;
    case GLFW_KEY_4:
      return PlaygroundKeyCode::k4;
    case GLFW_KEY_5:
      return PlaygroundKeyCode::k5;
    case GLFW_KEY_6:
      return PlaygroundKeyCode::k6;
    case GLFW_KEY_7:
      return PlaygroundKeyCode::k7;
    case GLFW_KEY_8:
      return PlaygroundKeyCode::k8;
    case GLFW_KEY_9:
      return PlaygroundKeyCode::k9;
    case GLFW_KEY_SEMICOLON:
      return PlaygroundKeyCode::kSemicolon;
    case GLFW_KEY_EQUAL:
      return PlaygroundKeyCode::kEqual;
    case GLFW_KEY_A:
      return PlaygroundKeyCode::kA;
    case GLFW_KEY_B:
      return PlaygroundKeyCode::kB;
    case GLFW_KEY_C:
      return PlaygroundKeyCode::kC;
    case GLFW_KEY_D:
      return PlaygroundKeyCode::kD;
    case GLFW_KEY_E:
      return PlaygroundKeyCode::kE;
    case GLFW_KEY_F:
      return PlaygroundKeyCode::kF;
    case GLFW_KEY_G:
      return PlaygroundKeyCode::kG;
    case GLFW_KEY_H:
      return PlaygroundKeyCode::kH;
    case GLFW_KEY_I:
      return PlaygroundKeyCode::kI;
    case GLFW_KEY_J:
      return PlaygroundKeyCode::kJ;
    case GLFW_KEY_K:
      return PlaygroundKeyCode::kK;
    case GLFW_KEY_L:
      return PlaygroundKeyCode::kL;
    case GLFW_KEY_M:
      return PlaygroundKeyCode::kM;
    case GLFW_KEY_N:
      return PlaygroundKeyCode::kN;
    case GLFW_KEY_O:
      return PlaygroundKeyCode::kO;
    case GLFW_KEY_P:
      return PlaygroundKeyCode::kP;
    case GLFW_KEY_Q:
      return PlaygroundKeyCode::kQ;
    case GLFW_KEY_R:
      return PlaygroundKeyCode::kR;
    case GLFW_KEY_S:
      return PlaygroundKeyCode::kS;
    case GLFW_KEY_T:
      return PlaygroundKeyCode::kT;
    case GLFW_KEY_U:
      return PlaygroundKeyCode::kU;
    case GLFW_KEY_V:
      return PlaygroundKeyCode::kV;
    case GLFW_KEY_W:
      return PlaygroundKeyCode::kW;
    case GLFW_KEY_X:
      return PlaygroundKeyCode::kX;
    case GLFW_KEY_Y:
      return PlaygroundKeyCode::kY;
    case GLFW_KEY_Z:
      return PlaygroundKeyCode::kZ;
    case GLFW_KEY_LEFT_BRACKET:
      return PlaygroundKeyCode::kLeftBracket;
    case GLFW_KEY_BACKSLASH:
      return PlaygroundKeyCode::kBackslash;
    case GLFW_KEY_RIGHT_BRACKET:
      return PlaygroundKeyCode::kRightBracket;
    case GLFW_KEY_GRAVE_ACCENT:
      return PlaygroundKeyCode::kGraveAccent;
    case GLFW_KEY_WORLD_1:
      return PlaygroundKeyCode::kWorld1;
    case GLFW_KEY_WORLD_2:
      return PlaygroundKeyCode::kWorld2;
    case GLFW_KEY_ESCAPE:
      return PlaygroundKeyCode::kEscape;
    case GLFW_KEY_ENTER:
      return PlaygroundKeyCode::kEnter;
    case GLFW_KEY_TAB:
      return PlaygroundKeyCode::kTab;
    case GLFW_KEY_BACKSPACE:
      return PlaygroundKeyCode::kBackspace;
    case GLFW_KEY_INSERT:
      return PlaygroundKeyCode::kInsert;
    case GLFW_KEY_DELETE:
      return PlaygroundKeyCode::kDelete;
    case GLFW_KEY_RIGHT:
      return PlaygroundKeyCode::kRight;
    case GLFW_KEY_LEFT:
      return PlaygroundKeyCode::kLeft;
    case GLFW_KEY_DOWN:
      return PlaygroundKeyCode::kDown;
    case GLFW_KEY_UP:
      return PlaygroundKeyCode::kUp;
    case GLFW_KEY_PAGE_UP:
      return PlaygroundKeyCode::kPageUp;
    case GLFW_KEY_PAGE_DOWN:
      return PlaygroundKeyCode::kPageDown;
    case GLFW_KEY_HOME:
      return PlaygroundKeyCode::kHome;
    case GLFW_KEY_END:
      return PlaygroundKeyCode::kEnd;
    case GLFW_KEY_CAPS_LOCK:
      return PlaygroundKeyCode::kCapsLock;
    case GLFW_KEY_SCROLL_LOCK:
      return PlaygroundKeyCode::kScrollLock;
    case GLFW_KEY_NUM_LOCK:
      return PlaygroundKeyCode::kNumLock;
    case GLFW_KEY_PRINT_SCREEN:
      return PlaygroundKeyCode::kPrintScreen;
    case GLFW_KEY_PAUSE:
      return PlaygroundKeyCode::kPause;
    case GLFW_KEY_F1:
      return PlaygroundKeyCode::kFunction1;
    case GLFW_KEY_F2:
      return PlaygroundKeyCode::kFunction2;
    case GLFW_KEY_F3:
      return PlaygroundKeyCode::kFunction3;
    case GLFW_KEY_F4:
      return PlaygroundKeyCode::kFunction4;
    case GLFW_KEY_F5:
      return PlaygroundKeyCode::kFunction5;
    case GLFW_KEY_F6:
      return PlaygroundKeyCode::kFunction6;
    case GLFW_KEY_F7:
      return PlaygroundKeyCode::kFunction7;
    case GLFW_KEY_F8:
      return PlaygroundKeyCode::kFunction8;
    case GLFW_KEY_F9:
      return PlaygroundKeyCode::kFunction9;
    case GLFW_KEY_F10:
      return PlaygroundKeyCode::kFunction10;
    case GLFW_KEY_F11:
      return PlaygroundKeyCode::kFunction11;
    case GLFW_KEY_F12:
      return PlaygroundKeyCode::kFunction12;
    case GLFW_KEY_F13:
      return PlaygroundKeyCode::kFunction13;
    case GLFW_KEY_F14:
      return PlaygroundKeyCode::kFunction14;
    case GLFW_KEY_F15:
      return PlaygroundKeyCode::kFunction15;
    case GLFW_KEY_F16:
      return PlaygroundKeyCode::kFunction16;
    case GLFW_KEY_F17:
      return PlaygroundKeyCode::kFunction17;
    case GLFW_KEY_F18:
      return PlaygroundKeyCode::kFunction18;
    case GLFW_KEY_F19:
      return PlaygroundKeyCode::kFunction19;
    case GLFW_KEY_F20:
      return PlaygroundKeyCode::kFunction20;
    case GLFW_KEY_F21:
      return PlaygroundKeyCode::kFunction21;
    case GLFW_KEY_F22:
      return PlaygroundKeyCode::kFunction22;
    case GLFW_KEY_F23:
      return PlaygroundKeyCode::kFunction23;
    case GLFW_KEY_F24:
      return PlaygroundKeyCode::kFunction24;
    case GLFW_KEY_F25:
      return PlaygroundKeyCode::kFunction25;
    case GLFW_KEY_KP_0:
      return PlaygroundKeyCode::kKeyPad0;
    case GLFW_KEY_KP_1:
      return PlaygroundKeyCode::kKeyPad1;
    case GLFW_KEY_KP_2:
      return PlaygroundKeyCode::kKeyPad2;
    case GLFW_KEY_KP_3:
      return PlaygroundKeyCode::kKeyPad3;
    case GLFW_KEY_KP_4:
      return PlaygroundKeyCode::kKeyPad4;
    case GLFW_KEY_KP_5:
      return PlaygroundKeyCode::kKeyPad5;
    case GLFW_KEY_KP_6:
      return PlaygroundKeyCode::kKeyPad6;
    case GLFW_KEY_KP_7:
      return PlaygroundKeyCode::kKeyPad7;
    case GLFW_KEY_KP_8:
      return PlaygroundKeyCode::kKeyPad8;
    case GLFW_KEY_KP_9:
      return PlaygroundKeyCode::kKeyPad9;
    case GLFW_KEY_KP_DECIMAL:
      return PlaygroundKeyCode::kKeyPadDecimal;
    case GLFW_KEY_KP_DIVIDE:
      return PlaygroundKeyCode::kKeyPadDivide;
    case GLFW_KEY_KP_MULTIPLY:
      return PlaygroundKeyCode::kKeyPadMultiply;
    case GLFW_KEY_KP_SUBTRACT:
      return PlaygroundKeyCode::kKeyPadSubtract;
    case GLFW_KEY_KP_ADD:
      return PlaygroundKeyCode::kKeyPadAdd;
    case GLFW_KEY_KP_ENTER:
      return PlaygroundKeyCode::kKeyPadEnter;
    case GLFW_KEY_KP_EQUAL:
      return PlaygroundKeyCode::kKeyPadEqual;
    case GLFW_KEY_LEFT_SHIFT:
      return PlaygroundKeyCode::kLeftShift;
    case GLFW_KEY_LEFT_CONTROL:
      return PlaygroundKeyCode::kLeftControl;
    case GLFW_KEY_LEFT_ALT:
      return PlaygroundKeyCode::kLeftAlt;
    case GLFW_KEY_LEFT_SUPER:
      return PlaygroundKeyCode::kLeftSuper;
    case GLFW_KEY_RIGHT_SHIFT:
      return PlaygroundKeyCode::kRightShift;
    case GLFW_KEY_RIGHT_CONTROL:
      return PlaygroundKeyCode::kRightControl;
    case GLFW_KEY_RIGHT_ALT:
      return PlaygroundKeyCode::kRightAlt;
    case GLFW_KEY_RIGHT_SUPER:
      return PlaygroundKeyCode::kRightSuper;
    case GLFW_KEY_MENU:
      return PlaygroundKeyCode::kMenu;
  }
  return std::nullopt;
}

PlaygroundWindowGLFW::PlaygroundWindowGLFW(PlaygroundWSIBackend backend)
    : backend_(backend) {
  ::glfwDefaultWindowHints();

  ::glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  switch (backend_) {
    case PlaygroundWSIBackend::kMetal:
      ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      break;
    case PlaygroundWSIBackend::kOpenGLES:
#if FML_OS_MACOSX
      // ES Profiles are not supported on Mac.
      ::glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
#else   // FML_OS_MACOSX
      ::glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
      ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif  // FML_OS_MACOSX
      ::glfwWindowHint(GLFW_RED_BITS, 8);
      ::glfwWindowHint(GLFW_GREEN_BITS, 8);
      ::glfwWindowHint(GLFW_BLUE_BITS, 8);
      ::glfwWindowHint(GLFW_ALPHA_BITS, 8);
      ::glfwWindowHint(GLFW_DEPTH_BITS, 32);   // 32 bit depth buffer
      ::glfwWindowHint(GLFW_STENCIL_BITS, 8);  // 8 bit stencil buffer
      ::glfwWindowHint(GLFW_SAMPLES, 4);       // 4xMSAA
      break;
    case PlaygroundWSIBackend::kVulkan:
      if (!::glfwVulkanSupported()) {
#ifdef TARGET_OS_MAC
        VALIDATION_LOG
            << "Attempted to initialize a Vulkan playground on macOS "
               "where Vulkan cannot be found. It can be installed via "
               "MoltenVK and make sure to install it globally so "
               "dlopen can find it.";
#else   // TARGET_OS_MAC
        VALIDATION_LOG
            << "Attempted to initialize a Vulkan playground on a system "
               "that does not support Vulkan.";
#endif  // TARGET_OS_MAC
        return;
      }
      ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      break;
  }

  auto window = ::glfwCreateWindow(1, 1, "Test", nullptr, nullptr);

  if (!window) {
    return;
  }

  // Window is valid. Now set it up.
  switch (backend_) {
    case PlaygroundWSIBackend::kMetal:
    case PlaygroundWSIBackend::kOpenGLES:
      ::glfwMakeContextCurrent(window);
    case PlaygroundWSIBackend::kVulkan:
      break;
  }

  ::glfwSetWindowUserPointer(window, this);
  ::glfwSetWindowSizeCallback(
      window, [](GLFWwindow* window, int width, int height) -> void {
        auto thiz = reinterpret_cast<PlaygroundWindowGLFW*>(
            ::glfwGetWindowUserPointer(window));
        if (!thiz) {
          return;
        }
        if (thiz->resize_callback_) {
          thiz->resize_callback_(ISize{width, height}.Max({}));
        }
      });

  window_ = window;
  is_valid_ = true;
}

PlaygroundWindowGLFW::~PlaygroundWindowGLFW() {
  if (window_) {
    ::glfwDestroyWindow(window_);
  }
}

bool PlaygroundWindowGLFW::IsValid() const {
  return is_valid_;
}

// |PlaygroundWindow|
ISize PlaygroundWindowGLFW::GetSize() const {
  if (!IsValid()) {
    return {};
  }
  int width = 0;
  int height = 0;
  ::glfwGetFramebufferSize(window_, &width, &height);
  if (width <= 0 || height <= 0) {
    return {};
  }
  return {width, height};
}

// |PlaygroundWindow|
Vector2 PlaygroundWindowGLFW::GetContentScale() const {
  if (!IsValid()) {
    return {1.0f, 1.0f};
  }
  Vector2 scale(1, 1);
  ::glfwGetWindowContentScale(window_, &scale.x, &scale.y);
  return scale;
}

using FunctionPointer = void (*)(void);
FunctionPointer PlaygroundWindowGLFW::GetVulkanInstanceProcAddressPointer()
    const {
  if (backend_ == PlaygroundWSIBackend::kVulkan) {
    return &::glfwGetInstanceProcAddress;
  }
}

void PlaygroundWindowGLFW::SetWindowTitle(const std::string& title) {
  ::glfwSetWindowTitle(window_, title.c_str());
}

void PlaygroundWindowGLFW::SetWindowSize(ISize size) {
  ::glfwSetWindowSize(window_, size.width, size.height);
}

}  // namespace impeller
