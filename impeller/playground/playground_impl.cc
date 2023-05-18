// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/playground_impl.h"

#include "impeller/playground/wsi/playground_window.h"

#if IMPELLER_ENABLE_METAL
#include "impeller/playground/backend/metal/playground_impl_mtl.h"
#endif  // IMPELLER_ENABLE_METAL

#if IMPELLER_ENABLE_OPENGLES
#include "impeller/playground/backend/gles/playground_impl_gles.h"
#endif  // IMPELLER_ENABLE_OPENGLES

#if IMPELLER_ENABLE_VULKAN
#include "impeller/playground/backend/vulkan/playground_impl_vk.h"
#endif  // IMPELLER_ENABLE_VULKAN

namespace impeller {

std::unique_ptr<PlaygroundImpl> PlaygroundImpl::Create(
    PlaygroundBackend backend,
    PlaygroundSwitches switches) {
  switch (backend) {
#if IMPELLER_ENABLE_METAL
    case PlaygroundBackend::kMetal:
      return std::make_unique<PlaygroundImplMTL>(switches);
#endif  // IMPELLER_ENABLE_METAL
#if IMPELLER_ENABLE_OPENGLES
    case PlaygroundBackend::kOpenGLES:
      return std::make_unique<PlaygroundImplGLES>(switches);
#endif  // IMPELLER_ENABLE_OPENGLES
#if IMPELLER_ENABLE_VULKAN
    case PlaygroundBackend::kVulkan:
      return std::make_unique<PlaygroundImplVK>(switches);
#endif  // IMPELLER_ENABLE_VULKAN
    default:
      FML_CHECK(false) << "Attempted to create playground with backend that "
                          "isn't available or was disabled on this platform: "
                       << PlaygroundBackendToString(backend);
  }
  FML_UNREACHABLE();
}

PlaygroundImpl::PlaygroundImpl(PlaygroundSwitches switches,
                               std::unique_ptr<PlaygroundWindow> window)
    : switches_(switches), window_(std::move(window)) {}

PlaygroundImpl::~PlaygroundImpl() = default;

Vector2 PlaygroundImpl::GetContentScale() const {
  if (!window_) {
    return {1.0f, 1.0f};
  }
  return window_->GetContentScale();
}

}  // namespace impeller
