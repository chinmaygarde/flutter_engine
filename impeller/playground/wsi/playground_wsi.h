// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include "flutter/fml/macros.h"

namespace impeller {

class PlaygroundWindow;

enum class PlaygroundWSIBackend {
  kMetal,
  kOpenGLES,
  kVulkan,
};

class PlaygroundWSI {
 public:
  static std::unique_ptr<PlaygroundWSI> Create();

  ~PlaygroundWSI();

  virtual std::unique_ptr<PlaygroundWindow> CreateWindow(
      PlaygroundWSIBackend backend) = 0;

 protected:
  PlaygroundWSI();

 private:
  FML_DISALLOW_COPY_AND_ASSIGN(PlaygroundWSI);
};

}  // namespace impeller
