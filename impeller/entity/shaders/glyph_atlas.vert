// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include <impeller/transform.glsl>
#include <impeller/types.glsl>

uniform FrameInfo {
  mat4 mvp;
}
frame_info;

in vec2 uv;
in vec2 position;
in vec4 debug_color;

out vec2 v_uv;
flat out vec4 v_debug_color;

void main() {
  gl_Position = frame_info.mvp * vec4(position, 0, 1);
  v_uv = uv;
  v_debug_color = debug_color;
}
