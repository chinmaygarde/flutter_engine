// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h"

#include "impeller/renderer/backend/vulkan/swapchain/khr/khr_swapchain_vk.h"

#if FML_OS_ANDROID
#include "impeller/renderer/backend/vulkan/swapchain/ahb/ahb_swapchain_vk.h"
#endif  // FML_OS_ANDROID

namespace impeller {

std::shared_ptr<SwapchainVK> SwapchainVK::Create(
    const std::shared_ptr<Context>& context,
    vk::UniqueSurfaceKHR surface,
    const ISize& size,
    bool enable_msaa) {
  return std::shared_ptr<KHRSwapchainVK>(
      new KHRSwapchainVK(context, std::move(surface), size, enable_msaa));
}

#if FML_OS_ANDROID
std::shared_ptr<SwapchainVK> SwapchainVK::Create(
    const std::shared_ptr<Context>& context,
    ANativeWindow* window,
    const ISize& size,
    bool enable_msaa) {
  return std::shared_ptr<AHBSwapchainVK>(
      new AHBSwapchainVK(context, window, size, enable_msaa));
}
#endif  // FML_OS_ANDROID

SwapchainVK::SwapchainVK() = default;

SwapchainVK::~SwapchainVK() = default;

}  // namespace impeller
