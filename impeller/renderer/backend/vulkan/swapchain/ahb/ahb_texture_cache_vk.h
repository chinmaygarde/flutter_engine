// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_TEXTURE_CACHE_VK_H_
#define FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_TEXTURE_CACHE_VK_H_

#include <deque>

#include "impeller/base/thread.h"
#include "impeller/base/timing.h"
#include "impeller/renderer/backend/vulkan/android/ahb_texture_source_vk.h"

namespace impeller {

class AHBTextureCacheVK {
 public:
  explicit AHBTextureCacheVK(
      std::weak_ptr<Context> context,
      android::HardwareBufferDescriptor desc,
      size_t max_entries = 2u,
      std::chrono::milliseconds max_extry_age = std::chrono::seconds{1});

  ~AHBTextureCacheVK();

  AHBTextureCacheVK(const AHBTextureCacheVK&) = delete;

  AHBTextureCacheVK& operator=(const AHBTextureCacheVK&) = delete;

  bool IsValid() const;

  std::shared_ptr<AHBTextureSourceVK> Pop();

  void Push(std::shared_ptr<AHBTextureSourceVK> texture);

  void PerformGC();

 private:
  struct CacheEntry {
    TimePoint last_access_time;
    std::shared_ptr<AHBTextureSourceVK> item;

    explicit CacheEntry(std::shared_ptr<AHBTextureSourceVK> p_item)
        : last_access_time(Clock::now()), item(std::move(p_item)) {}
  };

  const std::weak_ptr<Context> context_;
  const android::HardwareBufferDescriptor desc_;
  const size_t max_entries_;
  const std::chrono::milliseconds max_extry_age_;
  bool is_valid_ = false;
  Mutex cache_mutex_;
  std::deque<CacheEntry> cache_ IPLR_GUARDED_BY(cache_mutex_);

  void PerformGCLocked() IPLR_REQUIRES(cache_mutex_);

  std::shared_ptr<AHBTextureSourceVK> CreateTexture() const;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_SWAPCHAIN_AHB_AHB_TEXTURE_CACHE_VK_H_
