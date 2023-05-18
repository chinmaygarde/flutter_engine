// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <functional>

#include "flutter/fml/macros.h"
#include "impeller/playground/wsi/playground_window.h"
#include "impeller/playground/wsi/playground_wsi.h"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#import "third_party/glfw/include/GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_COCOA
#import "third_party/glfw/include/GLFW/glfw3native.h"
#include "third_party/imgui/backends/imgui_impl_glfw.h"

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

  using FunctionPointer = void (*)(void);
  FunctionPointer GetVulkanInstanceProcAddressPointer() const;

  using OpenPlaygroundCallback = std::function<bool(void)>;
  bool OpenPlaygroundHere(OpenPlaygroundCallback callback) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    fml::ScopedCleanupClosure destroy_imgui_context(
        []() { ImGui::DestroyContext(); });
    ImGui::StyleColorsDark();

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsResizeFromEdges = true;
  }

 private:
  const PlaygroundWSIBackend backend_;
  GLFWwindow* window_ = nullptr;
  bool is_valid_ = false;

  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWindowGLFW);
};

}  // namespace impeller
