// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/swapchain/swapchain_image_vk.h"

namespace impeller {

SwapchainImageVK::SwapchainImageVK(TextureDescriptor desc)
    : TextureSourceVK(desc) {}

SwapchainImageVK::~SwapchainImageVK() = default;

std::shared_ptr<Texture> SwapchainImageVK::GetMSAATexture() const {
  return msaa_texture_;
}

std::shared_ptr<Texture> SwapchainImageVK::GetDepthStencilTexture() const {
  return depth_stencil_texture_;
}

void SwapchainImageVK::SetMSAATexture(std::shared_ptr<Texture> texture) {
  msaa_texture_ = std::move(texture);
}

void SwapchainImageVK::SetDepthStencilTexture(
    std::shared_ptr<Texture> texture) {
  depth_stencil_texture_ = std::move(texture);
}

}  // namespace impeller
