// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_SWAPCHAIN_IMAGE_VK_H_
#define IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_SWAPCHAIN_IMAGE_VK_H_

#include "impeller/renderer/backend/vulkan/texture_source_vk.h"

namespace impeller {

class SwapchainImageVK : public TextureSourceVK {
 public:
  virtual ~SwapchainImageVK();

  SwapchainImageVK(const SwapchainImageVK&) = delete;

  SwapchainImageVK& operator=(const SwapchainImageVK&) = delete;

 protected:
  explicit SwapchainImageVK(TextureDescriptor desc);
};

}  // namespace impeller

#endif  // IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_SWAPCHAIN_IMAGE_VK_H_
