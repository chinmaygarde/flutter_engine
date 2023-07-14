// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <cstddef>
#include <map>
#include <optional>
#include <tuple>
#include <vector>

#include "flutter/fml/macros.h"
#include "impeller/core/formats.h"
#include "impeller/renderer/backend/vulkan/formats_vk.h"
#include "impeller/renderer/backend/vulkan/vk.h"

namespace impeller {

struct SubpassVK {
  std::map<size_t, Attachment> input_attachments;
  std::map<size_t, Attachment> color_attachments;
  std::optional<Attachment> depth_stencil_attachment;
};

struct SubpassesVK {
  std::vector<SubpassVK> subpasses;

  std::pair<vk::UniqueRenderPass, vk::UniqueFramebuffer>
  CreateRenderPassAndFramebuffer();
};

}  // namespace impeller
