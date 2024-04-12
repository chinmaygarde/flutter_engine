// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_SWAPCHAIN_IMPL_VK_H_
#define FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_SWAPCHAIN_IMPL_VK_H_

#include <memory>

#include "impeller/renderer/backend/vulkan/android/ahb_texture_source_vk.h"
#include "impeller/renderer/backend/vulkan/swapchain/ahb/ahb_texture_cache_vk.h"
#include "impeller/renderer/backend/vulkan/swapchain/swapchain_transients_vk.h"
#include "impeller/renderer/surface.h"
#include "impeller/toolkit/android/hardware_buffer.h"
#include "impeller/toolkit/android/surface_control.h"

namespace impeller {

class AHBSwapchainImplVK final
    : public std::enable_shared_from_this<AHBSwapchainImplVK> {
 public:
  static std::shared_ptr<AHBSwapchainImplVK> Create(
      const std::weak_ptr<Context>& context,
      std::weak_ptr<android::SurfaceControl> surface_control,
      const ISize& size,
      bool enable_msaa);

  ~AHBSwapchainImplVK();

  AHBSwapchainImplVK(const AHBSwapchainImplVK&) = delete;

  AHBSwapchainImplVK& operator=(const AHBSwapchainImplVK&) = delete;

  const ISize& GetSize() const;

  bool IsValid() const;

  const android::HardwareBufferDescriptor& GetDescriptor() const;

  std::unique_ptr<Surface> AcquireNextDrawable();

 private:
  std::weak_ptr<android::SurfaceControl> surface_control_;
  android::HardwareBufferDescriptor desc_;
  std::shared_ptr<AHBTextureCacheVK> cache_;
  std::shared_ptr<SwapchainTransientsVK> transients_;
  bool is_valid_ = false;

  explicit AHBSwapchainImplVK(
      const std::weak_ptr<Context>& context,
      std::weak_ptr<android::SurfaceControl> surface_control,
      const ISize& size,
      bool enable_msaa);

  bool Present(const std::shared_ptr<AHBTextureSourceVK>& texture);
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_SWAPCHAIN_IMPL_VK_H_
