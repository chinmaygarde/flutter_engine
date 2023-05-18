// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "flutter/fml/macros.h"
#include "impeller/playground/wsi/playground_wsi.h"

namespace impeller {

class PlaygroundWSIGLFW final : public PlaygroundWSI {
 public:
  PlaygroundWSIGLFW();

  ~PlaygroundWSIGLFW();

  // |PlaygroundWSI|
  std::unique_ptr<PlaygroundWindow> CreateWindow(
      PlaygroundWSIBackend backend) override;

 private:
  struct GLFWInitializer;

  std::unique_ptr<GLFWInitializer> glfw_initializer_;

  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWSIGLFW);
};

}  // namespace impeller
