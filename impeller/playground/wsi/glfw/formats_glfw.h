// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <optional>

#include "impeller/playground/wsi/formats.h"
#include "impeller/playground/wsi/glfw/glfw.h"

namespace impeller {

constexpr std::optional<PlaygroundKeyAction> ToPlaygroundKeyAction(int action) {
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

constexpr uint64_t ToPlaygroundKeyModifiers(int modifiers) {
  uint64_t mods = 0u;
  if (modifiers & GLFW_MOD_SHIFT) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kShift);
  }
  if (modifiers & GLFW_MOD_CONTROL) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kControl);
  }
  if (modifiers & GLFW_MOD_ALT) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kAlt);
  }
  if (modifiers & GLFW_MOD_SUPER) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kSuper);
  }
  if (modifiers & GLFW_MOD_CAPS_LOCK) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kCapsLock);
  }
  if (modifiers & GLFW_MOD_NUM_LOCK) {
    mods |= static_cast<uint64_t>(PlaygroundKeyModifier::kNumLock);
  }
  return mods;
}

constexpr std::optional<PlaygroundKeyCode> ToPlaygroundKeyCode(int keycode) {
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

}  // namespace impeller
