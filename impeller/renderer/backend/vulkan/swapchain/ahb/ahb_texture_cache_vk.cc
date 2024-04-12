// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/swapchain/ahb/ahb_texture_cache_vk.h"

namespace impeller {

AHBTextureCacheVK::AHBTextureCacheVK(std::weak_ptr<Context> context,
                                     android::HardwareBufferDescriptor desc,
                                     size_t max_entries,
                                     std::chrono::milliseconds max_extry_age)
    : context_(std::move(context)),
      desc_(desc),
      max_entries_(max_entries),
      max_extry_age_(max_extry_age) {
  if (!desc_.IsAllocatable()) {
    VALIDATION_LOG << "Swapchain image is not allocatable.";
    return;
  }
  is_valid_ = true;
}

AHBTextureCacheVK::~AHBTextureCacheVK() = default;

std::shared_ptr<AHBTextureSourceVK> AHBTextureCacheVK::Pop() {
  {
    Lock lock(cache_mutex_);
    if (!cache_.empty()) {
      auto texture = cache_.back().item;
      cache_.pop_back();
      return texture;
    }
  }
  return Create();
}

void AHBTextureCacheVK::Push(std::shared_ptr<AHBTextureSourceVK> texture) {
  Lock lock(cache_mutex_);
  cache_.push_back(CacheEntry{std::move(texture)});
  PerformGCLocked();
}

std::shared_ptr<AHBTextureSourceVK> AHBTextureCacheVK::Create() const {
  auto context = context_.lock();
  if (!context) {
    VALIDATION_LOG << "Context died before image could be created.";
    return nullptr;
  }

  auto ahb = std::make_unique<android::HardwareBuffer>(desc_);
  if (!ahb->IsValid()) {
    VALIDATION_LOG << "Could not create hardware buffer of size: "
                   << desc_.size;
    return nullptr;
  }

  auto ahb_texture_source =
      std::make_shared<AHBTextureSourceVK>(context, std::move(ahb), true);
  if (!ahb_texture_source->IsValid()) {
    VALIDATION_LOG << "Could not create hardware buffer texture source for "
                      "swapchain image of size: "
                   << desc_.size;
    return nullptr;
  }

  return ahb_texture_source;
}

void AHBTextureCacheVK::PerformGC() {
  Lock lock(cache_mutex_);
  PerformGCLocked();
}

void AHBTextureCacheVK::PerformGCLocked() {
  // Push-Pop operations happen at the back of the deque so the front ages as
  // much as possible. So that's where we collect entries.
  auto now = Clock::now();
  while (!cache_.empty() &&
         (cache_.size() > max_entries_ ||
          now - cache_.front().last_access_time >= max_extry_age_)) {
    cache_.pop_front();
  }
}

bool AHBTextureCacheVK::IsValid() const {
  return is_valid_;
}

}  // namespace impeller
