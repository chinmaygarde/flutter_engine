// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <functional>

#include "flutter/fml/macros.h"
#include "impeller/playground/wsi/playground_window.h"
#include "impeller/playground/wsi/playground_wsi.h"
#include "impeller/renderer/render_target.h"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "third_party/glfw/include/GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_COCOA
#include "third_party/glfw/include/GLFW/glfw3native.h"
#include "third_party/imgui/backends/imgui_impl_glfw.h"
#include "third_party/imgui/imgui.h"

namespace impeller {

class PlaygroundWindowGLFW final : public PlaygroundWindow {
 public:
  explicit PlaygroundWindowGLFW(PlaygroundWSIBackend backend);

  ~PlaygroundWindowGLFW();

  bool IsValid() const;

  // |PlaygroundWindow|
  ISize GetSize() const override;

  // |PlaygroundWindow|
  Vector2 GetContentScale() const override;

  // |PlaygroundWindow|
  void SetWindowTitle(const std::string& title) override;

  // |PlaygroundWindow|
  void SetWindowSize(ISize size) override;

  // |PlaygroundWindow|
  void SetWindowPosition(IPoint position) override;

  // |PlaygroundWindow|
  void SetWindowShouldClose() override;

  using FunctionPointer = void (*)(void);
  FunctionPointer GetVulkanInstanceProcAddressPointer() const;

  using OpenPlaygroundCallback = std::function<bool(RenderTarget&)>;
  bool OnOpenPlaygroundHere(std::shared_ptr<impeller::Context> context,
                            RenderTarget& render_target,
                            OpenPlaygroundCallback callback) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    fml::ScopedCleanupClosure destroy_imgui_context(
        []() { ImGui::DestroyContext(); });
    ImGui::StyleColorsDark();

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsResizeFromEdges = true;

    // Setup GLFW Imgui Hooks.
    ImGui_ImplGlfw_InitForOther(window_, true);
    fml::ScopedCleanupClosure shutdown_imgui(
        []() { ImGui_ImplGlfw_Shutdown(); });

    // Setup Impeller Imgui Hooks.
    ImGui_ImplImpeller_Init(renderer_->GetContext());
    fml::ScopedCleanupClosure shutdown_imgui_impeller(
        []() { ImGui_ImplImpeller_Shutdown(); });

    // Auto show the GLFW window.
    ::glfwShowWindow(window_);
    fml::ScopedCleanupClosure hide_glfw_window(
        [window = window_]() { ::glfwHideWindow(window); });

    ImGui::SetNextWindowPos({10, 10});

    while (true) {
      ::glfwPollEvents();

      if (::glfwWindowShouldClose(window_)) {
        return true;
      }
      if (!BeginNewImguiFrame()) {
        return false;
      }
      if (callback) {
        if (!callback(render_target)) {
          return false;
        }
      }
      if (!RenderImguiOverlay(render_target)) {
        return false;
      }
      if (on_render_frame_callback_) {
        if (!on_render_frame_callback_()) {
          return true;
        }
      }
    }

    return true;
  }

 private:
  const PlaygroundWSIBackend backend_;
  GLFWwindow* window_ = nullptr;
  bool is_valid_ = false;

  bool BeginNewImguiFrame() const {
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
                                 ImGuiDockNodeFlags_PassthruCentralNode);
    return true;
  }

  bool RenderImguiOverlay(RenderTarget& render_target) const {
    // Ask ImGUI to prep it buffers for render.
    ImGui::Render();

    auto buffer = renderer->GetContext()->CreateCommandBuffer();
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

  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWindowGLFW);
};

}  // namespace impeller
