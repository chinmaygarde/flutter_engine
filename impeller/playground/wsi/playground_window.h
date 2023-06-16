// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <functional>
#include <utility>

#include "flutter/fml/closure.h"
#include "flutter/fml/macros.h"
#include "impeller/geometry/size.h"
#include "impeller/geometry/vector.h"
#include "impeller/playground/wsi/formats.h"
#include "impeller/renderer/renderer.h"

namespace impeller {

class Surface;

class PlaygroundWindow {
 public:
  PlaygroundWindow();

  virtual ~PlaygroundWindow();

  virtual ISize GetSize() const = 0;

  virtual Vector2 GetContentScale() const = 0;

  virtual void SetWindowTitle(const std::string& title) = 0;

  virtual void SetWindowSize(ISize size) = 0;

  virtual void SetWindowPosition(IPoint position) = 0;

  virtual void SetWindowShouldClose() = 0;

  using ResizeCallback = std::function<void(ISize)>;
  void SetResizeCallback(ResizeCallback callback);

  using KeyCallback = std::function<void(PlaygroundKeyCode code,
                                         PlaygroundKeyAction action,
                                         uint64_t modifiers)>;
  void SetKeyCallback(KeyCallback callback);

  using CursorCallback = std::function<void(Point)>;
  void SetCursorCallback(CursorCallback callback);

  using OnRenderCallback = std::function<bool(void)>;
  void SetOnRenderFrameCallback(OnRenderCallback callback);

  using SurfaceAcquireCallback = std::function<std::unique_ptr<Surface>(void)>;
  void SetSurfaceAcquireCallback(SurfaceAcquireCallback callback);

  virtual bool Render(const Renderer& renderer,
                      Renderer::RenderCallback render_callback) = 0;

 protected:
  ResizeCallback resize_callback_;
  KeyCallback key_callback_;
  CursorCallback cursor_callback_;
  OnRenderCallback on_render_frame_callback_;
  SurfaceAcquireCallback surface_acquire_callback_;

 private:
  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWindow);
};

}  // namespace impeller
