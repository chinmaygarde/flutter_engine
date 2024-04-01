// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_KHR_KHR_SWAPCHAIN_IMAGE_VK_H_
#define FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_KHR_KHR_SWAPCHAIN_IMAGE_VK_H_

#include "impeller/geometry/size.h"
#include "impeller/renderer/backend/vulkan/formats_vk.h"
#include "impeller/renderer/backend/vulkan/texture_source_vk.h"
#include "impeller/renderer/backend/vulkan/vk.h"
#include "vulkan/vulkan_handles.hpp"

namespace impeller {

class SwapchainImageBackingStoreVK;

class SwapchainImageVK final : public TextureSourceVK {
 public:
  SwapchainImageVK(TextureDescriptor desc,
                   const vk::Device& device,
                   vk::Image image);

  // |TextureSourceVK|
  ~SwapchainImageVK() override;

  bool IsValid() const;

  PixelFormat GetPixelFormat() const;

  ISize GetSize() const;

  // |TextureSourceVK|
  vk::Image GetImage() const override;

  // |TextureSourceVK|
  vk::ImageView GetImageView() const override;

  // |TextureSourceVK|
  vk::ImageView GetRenderTargetView() const override;

  // |TextureSourceVK|
  bool IsSwapchainImage() const override;

  std::shared_ptr<Texture> GetMSAATexture() const;

  std::shared_ptr<Texture> GetDepthStencilTexture() const;

  void SetMSAATexture(std::shared_ptr<Texture> texture);

  void SetDepthStencilTexture(std::shared_ptr<Texture> texture);

 private:
  vk::Image image_ = VK_NULL_HANDLE;
  vk::UniqueImageView image_view_ = {};
  std::shared_ptr<Texture> msaa_texture_;
  std::shared_ptr<Texture> depth_stencil_texture_;
  bool is_valid_ = false;

  SwapchainImageVK(const SwapchainImageVK&) = delete;

  SwapchainImageVK& operator=(const SwapchainImageVK&) = delete;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_KHR_KHR_SWAPCHAIN_IMAGE_VK_H_
