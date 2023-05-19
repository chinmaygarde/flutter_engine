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
#include "impeller/base/auto_release_pool.h"
#include "impeller/base/validation.h"
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

  // |PlaygroundWindow|
  bool Render(const Renderer& renderer,
              Renderer::RenderCallback render_callback) override {
    if (!render_callback) {
      return false;
    }
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
    ImGui_ImplImpeller_Init(renderer.GetContext());
    fml::ScopedCleanupClosure shutdown_imgui_impeller(
        []() { ImGui_ImplImpeller_Shutdown(); });

    // Auto show the GLFW window.
    ::glfwShowWindow(window_);
    fml::ScopedCleanupClosure hide_glfw_window(
        [window = window_]() { ::glfwHideWindow(window); });

    ImGui::SetNextWindowPos({10, 10});

    while (true) {
      AutoReleasePool frame_pool;
      ::glfwPollEvents();
      if (::glfwWindowShouldClose(window_)) {
        return true;
      }
      auto surface =
          surface_acquire_callback_ ? surface_acquire_callback_() : nullptr;
      if (!surface) {
        VALIDATION_LOG << "Could not acquire surface to render to.";
        return false;
      }
      // Renders the playground contents but also overlays the ImGui windows on
      // top before rendering.
      Renderer::RenderCallback wrapped_render_callback =
          [&](RenderTarget& target) {
            if (!BeginNewImguiFrame()) {
              return false;
            }
            if (!render_callback(target)) {
              VALIDATION_LOG
                  << "Could not render playground contents to surface.";
              return false;
            }
            if (!RenderImguiOverlay(target)) {
              VALIDATION_LOG << "Could not render ImGui overlay to surface.";
              return false;
            }
          };

      if (!renderer.Render(std::move(surface), wrapped_render_callback)) {
        VALIDATION_LOG << "Could not render playground contents to surface.";
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

  bool BeginNewImguiFrame() const;

  bool RenderImguiOverlay(std::shared_ptr<impeller::Context> context,
                          RenderTarget& render_target) const;

  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWindowGLFW);
};

}  // namespace impeller
