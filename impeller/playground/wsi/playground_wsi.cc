// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/wsi/playground_wsi.h"

#include "impeller/playground/wsi/glfw/playground_wsi_glfw.h"

namespace impeller {

std::unique_ptr<PlaygroundWSI> PlaygroundWSI::Create() {
  return std::make_unique<PlaygroundWSIGLFW>();
}

PlaygroundWSI::PlaygroundWSI() = default;

PlaygroundWSI::~PlaygroundWSI() = default;

}  // namespace impeller
