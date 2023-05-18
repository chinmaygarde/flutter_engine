// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/wsi/playground_window.h"

#include <utility>

namespace impeller {

PlaygroundWindow::PlaygroundWindow() = default;

PlaygroundWindow::~PlaygroundWindow() = default;

void PlaygroundWindow::SetResizeCallback(ResizeCallback callback) {
  resize_callback_ = std::move(callback);
}

}  // namespace impeller
