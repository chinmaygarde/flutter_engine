// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/wsi/glfw/playground_window_glfw.h"

#include <optional>
#include "flutter/fml/logging.h"
#include "impeller/base/validation.h"

namespace impeller {

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
          thiz->resize_callback_(ISize{width, height});
        }
      });
  ::glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
    auto playground_keycode = ToPlaygroundKeyCode(key);
    auto playground_action = ToPlaygroundKeyAction(action);
    auto playground_modifiers = ToPlaygroundKeyModifiers(mods);
    if (!playground_keycode.has_value() || !playground_action.has_value()) {
      VALIDATION_LOG << "Unknown playground key or action.";
      return;
    }
    auto thiz = reinterpret_cast<PlaygroundWindowGLFW*>(
        ::glfwGetWindowUserPointer(window));
    if (!thiz) {
      return;
    }
    if (thiz->key_callback_) {
      thiz->key_callback_(playground_keycode.value(),  //
                          playground_action.value(),   //
                          playground_modifiers         //
      );
    }
  });
  ::glfwSetCursorPosCallback(
      window, [](GLFWwindow* window, double x, double y) {
        auto thiz = reinterpret_cast<PlaygroundWindowGLFW*>(
            ::glfwGetWindowUserPointer(window));
        if (!thiz) {
          return;
        }
        if (thiz->cursor_callback_) {
          thiz->cursor_callback_(
              Point{static_cast<Scalar>(x), static_cast<Scalar>(y)});
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

void PlaygroundWindowGLFW::SetWindowPosition(IPoint position) {
  ::glfwSetWindowPos(window_, position.x, position.y);
}

void PlaygroundWindowGLFW::SetWindowShouldClose() {
  ::glfwWindowShouldClose(window_);
}

bool PlaygroundWindowGLFW::BeginNewImguiFrame() const {
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
                               ImGuiDockNodeFlags_PassthruCentralNode);
  return true;
}
bool PlaygroundWindowGLFW::RenderImguiOverlay(
    std::shared_ptr<impeller::Context> context,
    RenderTarget& render_target) const {
  // Ask ImGUI to prep it buffers for render.
  ImGui::Render();
  if (!context) {
    return false;
  }
  auto buffer = context->CreateCommandBuffer();
  if (!buffer) {
    return false;
  }
  buffer->SetLabel("ImGui Command Buffer");

  if (render_target.GetColorAttachments().empty()) {
    return false;
  }

  auto color0 = render_target.GetColorAttachments().find(0)->second;
  color0.load_action = LoadAction::kLoad;
  if (color0.resolve_texture) {
    color0.texture = color0.resolve_texture;
    color0.resolve_texture = nullptr;
    color0.store_action = StoreAction::kStore;
  }
  render_target.SetColorAttachment(color0, 0);

  render_target.SetStencilAttachment(std::nullopt);
  render_target.SetDepthAttachment(std::nullopt);

  auto imgui_pass = buffer->CreateRenderPass(render_target);
  if (!imgui_pass) {
    return false;
  }
  imgui_pass->SetLabel("ImGui Render Pass");

  ImGui_ImplImpeller_RenderDrawData(ImGui::GetDrawData(), *imgui_pass);

  imgui_pass->EncodeCommands();
  if (!buffer->SubmitCommands()) {
    return false;
  }
  return true;
}
}  // namespace impeller
