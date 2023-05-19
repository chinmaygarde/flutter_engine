// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <functional>
#include <utility>

#include "flutter/fml/closure.h"
#include "flutter/fml/macros.h"
#include "impeller/base/auto_release_pool.h"
#include "impeller/geometry/size.h"
#include "impeller/geometry/vector.h"
#include "impeller/renderer/renderer.h"

namespace impeller {

enum class PlaygroundKeyCode {
  kSpace,
  kApostrophe,
  kComma,
  kMinus,
  kPeriod,
  kSlash,
  k0,
  k1,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  kSemicolon,
  kEqual,
  kA,
  kB,
  kC,
  kD,
  kE,
  kF,
  kG,
  kH,
  kI,
  kJ,
  kK,
  kL,
  kM,
  kN,
  kO,
  kP,
  kQ,
  kR,
  kS,
  kT,
  kU,
  kV,
  kW,
  kX,
  kY,
  kZ,
  kLeftBracket,
  kBackslash,
  kRightBracket,
  kGraveAccent,
  kWorld1,
  kWorld2,
  kEscape,
  kEnter,
  kTab,
  kBackspace,
  kInsert,
  kDelete,
  kRight,
  kLeft,
  kDown,
  kUp,
  kPageUp,
  kPageDown,
  kHome,
  kEnd,
  kCapsLock,
  kScrollLock,
  kNumLock,
  kPrintScreen,
  kPause,
  kFunction1,
  kFunction2,
  kFunction3,
  kFunction4,
  kFunction5,
  kFunction6,
  kFunction7,
  kFunction8,
  kFunction9,
  kFunction10,
  kFunction11,
  kFunction12,
  kFunction13,
  kFunction14,
  kFunction15,
  kFunction16,
  kFunction17,
  kFunction18,
  kFunction19,
  kFunction20,
  kFunction21,
  kFunction22,
  kFunction23,
  kFunction24,
  kFunction25,
  kKeyPad0,
  kKeyPad1,
  kKeyPad2,
  kKeyPad3,
  kKeyPad4,
  kKeyPad5,
  kKeyPad6,
  kKeyPad7,
  kKeyPad8,
  kKeyPad9,
  kKeyPadDecimal,
  kKeyPadDivide,
  kKeyPadMultiply,
  kKeyPadSubtract,
  kKeyPadAdd,
  kKeyPadEnter,
  kKeyPadEqual,
  kLeftShift,
  kLeftControl,
  kLeftAlt,
  kLeftSuper,
  kRightShift,
  kRightControl,
  kRightAlt,
  kRightSuper,
  kMenu,
};

enum class PlaygroundKeyAction {
  kPress,
  kRelease,
  kRepeat,
};

enum class PlaygroundKeyModifier : uint64_t {
  kShift = 1 << 0,
  kControl = 1 << 1,
  kAlt = 1 << 2,
  kSuper = 1 << 3,
  kCapsLock = 1 << 4,
  kNumLock = 1 << 5,
};

class Surface;

class PlaygroundWindow {
 public:
  PlaygroundWindow();

  ~PlaygroundWindow();

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

  bool Render(const Renderer& renderer,
              Renderer::RenderCallback render_callback) {
    auto surface =
        surface_acquire_callback_ ? surface_acquire_callback_() : nullptr;
    if (!surface) {
      return false;
    }
    Renderer::RenderCallback wrapped_render_callback = [render_callback](
                                                           auto render_target) {
      AutoReleasePool pool;
      auto result = render_callback ? render_callback(render_target) : false;
      if (!result) {
        VALIDATION_LOG << "Could not render to surface.";
        return false;
      }
      return true;
    };
    return renderer.Render(std::move(surface), wrapped_render_callback);
  }

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
