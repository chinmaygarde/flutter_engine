// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/subpass_vk.h"

#include "impeller/renderer/backend/vulkan/texture_vk.h"

namespace impeller {

static vk::AttachmentDescription CreateAttachmentDescription(
    const Texture& texture,
    LoadAction load_action,
    StoreAction store_action) {
  const auto& texture_vk = TextureVK::Cast(texture);
  const auto& desc = texture.GetTextureDescriptor();
  const auto current_layout = texture_vk.GetLayout();

  if (current_layout == vk::ImageLayout::eUndefined) {
    load_action = LoadAction::kClear;
  }

  if (desc.storage_mode == StorageMode::kDeviceTransient) {
    store_action = StoreAction::kDontCare;
  }

  return CreateAttachmentDescription(desc.format,        //
                                     desc.sample_count,  //
                                     load_action,        //
                                     store_action,       //
                                     current_layout      //
  );
}

std::pair<vk::UniqueRenderPass, vk::UniqueFramebuffer>
SubpassesVK::CreateRenderPassAndFramebuffer() {
  std::vector<vk::AttachmentDescription> attachment_descs;
  std::vector<vk::ImageView> attachment_views;

  std::vector<vk::SubpassDescription> subpass_descs;
  subpass_descs.resize(subpasses.size());
  for (size_t i = 0u; i < subpasses.size(); i++) {
    std::vector<vk::AttachmentReference> input_refs;
    std::vector<vk::AttachmentReference> color_refs;
    std::vector<vk::AttachmentReference> resolve_refs;
    vk::AttachmentReference depth_stencil_ref = kUnusedAttachmentReference;

    auto& subpass_desc = subpass_descs[i];
    subpass_desc.setInputAttachments(input_refs);

    // Get the input attachments.
    for (const auto& [_, attachment] : subpass.input_attachments) {
      attachements_views.push_back(
          TextureVK::Cast(*attachment.texture).GetImageView());
      attachment_descs.push_back(
          CreateAttachmentDescription(attachment, false));
    }

    // Get the color attachemnts.

    // Get the depth-stencil attachment.
  }

  return {};
}

}  // namespace impeller
