// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
#define FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_

#include <memory>

#include "impeller/geometry/size.h"
#include "impeller/renderer/backend/vulkan/vk.h"
#include "impeller/renderer/surface.h"

namespace impeller {

//------------------------------------------------------------------------------
/// @brief      Describes a series of drawables that can be presented by the
///             system compositor in the window system on a platform.
///
class SwapchainVK {
 public:
  SwapchainVK();

  virtual ~SwapchainVK();

  SwapchainVK(const SwapchainVK&) = delete;

  SwapchainVK& operator=(const SwapchainVK&) = delete;

  //----------------------------------------------------------------------------
  /// @brief      Acquires the next drawable to present to. There may be a block
  ///             call in case the system compositor is busy presenting a
  ///             previous image.
  ///
  /// @return     If a drawable to present to could be obtained. `nullptr`
  ///             otherwise.
  ///
  virtual std::unique_ptr<Surface> AcquireNextDrawable() = 0;

  //----------------------------------------------------------------------------
  /// @brief      Get the format of the drawables in this swapchain.
  ///
  /// @return     The surface format of the drawables.
  ///
  virtual vk::Format GetSurfaceFormat() const = 0;

  //----------------------------------------------------------------------------
  /// @brief      Mark the current swapchain configuration as dirty, forcing it
  ///             to be recreated on the next frame.
  ///
  /// @param[in]  size  The new size in pixels.
  ///
  virtual void UpdateSurfaceSize(const ISize& size) = 0;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
