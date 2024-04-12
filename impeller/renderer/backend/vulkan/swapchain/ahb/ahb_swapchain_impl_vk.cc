// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/swapchain/ahb/ahb_swapchain_impl_vk.h"

#include "impeller/base/validation.h"
#include "impeller/renderer/backend/vulkan/swapchain/ahb/ahb_formats.h"
#include "impeller/renderer/backend/vulkan/swapchain/surface_vk.h"
#include "impeller/toolkit/android/surface_transaction.h"

namespace impeller {

static TextureDescriptor ToSwapchainTextureDescriptor(
    const android::HardwareBufferDescriptor& ahb_desc) {
  TextureDescriptor desc;
  desc.storage_mode = StorageMode::kDevicePrivate;
  desc.type = TextureType::kTexture2D;
  desc.format = ToPixelFormat(ahb_desc.format);
  desc.size = ahb_desc.size;
  desc.mip_count = 1u;
  desc.usage = TextureUsage::kRenderTarget;
  desc.sample_count = SampleCount::kCount1;
  desc.compression_type = CompressionType::kLossless;
  return desc;
}

std::shared_ptr<AHBSwapchainImplVK> AHBSwapchainImplVK::Create(
    const std::weak_ptr<Context>& context,
    std::weak_ptr<android::SurfaceControl> surface_control,
    const ISize& size,
    bool enable_msaa) {
  auto impl = std::shared_ptr<AHBSwapchainImplVK>(new AHBSwapchainImplVK(
      context, std::move(surface_control), size, enable_msaa));
  return impl->IsValid() ? impl : nullptr;
}

AHBSwapchainImplVK::AHBSwapchainImplVK(
    const std::weak_ptr<Context>& context,
    std::weak_ptr<android::SurfaceControl> surface_control,
    const ISize& size,
    bool enable_msaa)
    : surface_control_(std::move(surface_control)) {
  desc_ = android::HardwareBufferDescriptor::MakeForSwapchainImage(size);
  pool_ = std::make_shared<AHBTexturePoolVK>(context, desc_);
  if (!pool_->IsValid()) {
    return;
  }
  transients_ = std::make_shared<SwapchainTransientsVK>(
      context, ToSwapchainTextureDescriptor(desc_), enable_msaa);
  is_valid_ = true;
}

AHBSwapchainImplVK::~AHBSwapchainImplVK() = default;

const ISize& AHBSwapchainImplVK::GetSize() const {
  return desc_.size;
}

bool AHBSwapchainImplVK::IsValid() const {
  return is_valid_;
}

const android::HardwareBufferDescriptor& AHBSwapchainImplVK::GetDescriptor()
    const {
  return desc_;
}

std::unique_ptr<Surface> AHBSwapchainImplVK::AcquireNextDrawable() {
  if (!is_valid_) {
    return nullptr;
  }

  auto texture = pool_->Pop();

  if (!texture) {
    VALIDATION_LOG << "Could not create AHB texture source.";
    return nullptr;
  }

  return SurfaceVK::WrapSwapchainImage(
      transients_, texture, [weak = weak_from_this(), texture]() {
        auto thiz = weak.lock();
        if (!thiz) {
          VALIDATION_LOG << "Swapchain died before image could be presented.";
          return false;
        }
        return thiz->Present(texture);
      });
}

bool AHBSwapchainImplVK::Present(
    const std::shared_ptr<AHBTextureSourceVK>& texture) {
  auto control = surface_control_.lock();
  if (!control || !control->IsValid()) {
    VALIDATION_LOG << "Surface control died before swapchain image could be "
                      "presented.";
    return false;
  }
  android::SurfaceTransaction transaction;
  if (!transaction.SetContents(control.get(), texture->GetBackingStore())) {
    VALIDATION_LOG << "Could not set swapchain image contents on the surface "
                      "control.";
    return false;
  }
  return transaction.Apply([texture, weak = weak_from_this()]() {
    auto thiz = weak.lock();
    if (!thiz) {
      return;
    }
    thiz->pool_->Push(texture);
  });
}

}  // namespace impeller
