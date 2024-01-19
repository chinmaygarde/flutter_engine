// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/renderer/backend/vulkan/render_pass_builder_vk.h"

#include <algorithm>
#include <vector>

#include "impeller/renderer/backend/vulkan/formats_vk.h"

namespace impeller {

RenderPassBuilderVK::RenderPassBuilderVK() = default;

RenderPassBuilderVK::~RenderPassBuilderVK() = default;

RenderPassBuilderVK& RenderPassBuilderVK::SetColorAttachment(
    size_t index,
    PixelFormat format,
    SampleCount sample_count,
    LoadAction load_action,
    StoreAction store_action) {
  vk::AttachmentDescription desc;
  desc.format = ToVKImageFormat(format);
  desc.samples = ToVKSampleCount(sample_count);
  desc.loadOp = ToVKAttachmentLoadOp(load_action);
  desc.storeOp = ToVKAttachmentStoreOp(store_action);
  desc.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
  desc.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  desc.initialLayout = vk::ImageLayout::eGeneral;
  desc.finalLayout = vk::ImageLayout::eGeneral;
  colors_[index] = desc;

  desc.samples = vk::SampleCountFlagBits::e1;
  resolves_[index] = desc;

  return *this;
}

RenderPassBuilderVK& RenderPassBuilderVK::SetDepthStencilAttachment(
    PixelFormat format,
    SampleCount sample_count,
    LoadAction load_action,
    StoreAction store_action) {
  vk::AttachmentDescription desc;
  desc.format = ToVKImageFormat(format);
  desc.samples = ToVKSampleCount(sample_count);
  desc.loadOp = ToVKAttachmentLoadOp(load_action);
  desc.storeOp = ToVKAttachmentStoreOp(store_action);
  desc.stencilLoadOp = desc.loadOp;    // Not separable in Impeller.
  desc.stencilStoreOp = desc.storeOp;  // Not separable in Impeller.
  desc.initialLayout = vk::ImageLayout::eGeneral;
  desc.finalLayout = vk::ImageLayout::eGeneral;
  depth_stencil_ = desc;
  return *this;
}

RenderPassBuilderVK& RenderPassBuilderVK::SetStencilAttachment(
    PixelFormat format,
    SampleCount sample_count,
    LoadAction load_action,
    StoreAction store_action) {
  vk::AttachmentDescription desc;
  desc.format = ToVKImageFormat(format);
  desc.samples = ToVKSampleCount(sample_count);
  desc.loadOp = vk::AttachmentLoadOp::eDontCare;
  desc.storeOp = vk::AttachmentStoreOp::eDontCare;
  desc.stencilLoadOp = ToVKAttachmentLoadOp(load_action);
  desc.stencilStoreOp = ToVKAttachmentStoreOp(store_action);
  desc.initialLayout = vk::ImageLayout::eGeneral;
  desc.finalLayout = vk::ImageLayout::eGeneral;
  depth_stencil_ = desc;
  return *this;
}

vk::UniqueRenderPass RenderPassBuilderVK::Build(
    const vk::Device& device) const {
  if (colors_.empty()) {
    return {};
  }

  FML_DCHECK(colors_.size() == resolves_.size());

  // This must be less than `VkPhysicalDeviceLimits::maxColorAttachments` but we
  // are not checking.
  const auto color_attachments_count = colors_.rbegin()->first + 1u;

  std::vector<vk::AttachmentDescription> attachments;

  std::vector<vk::AttachmentReference> color_refs(color_attachments_count,
                                                  kUnusedAttachmentReference);
  std::vector<vk::AttachmentReference> resolve_refs(color_attachments_count,
                                                    kUnusedAttachmentReference);
  vk::AttachmentReference depth_stencil_ref = kUnusedAttachmentReference;

  for (const auto& color : colors_) {
    vk::AttachmentReference color_ref;
    color_ref.attachment = attachments.size();
    color_ref.layout = vk::ImageLayout::eGeneral;
    color_refs[color.first] = color_ref;
    attachments.push_back(color.second);

    if (color.second.samples != vk::SampleCountFlagBits::e1) {
      vk::AttachmentReference resolve_ref;
      resolve_ref.attachment = attachments.size();
      resolve_ref.layout = vk::ImageLayout::eGeneral;
      resolve_refs[color.first] = resolve_ref;
      attachments.push_back(resolves_.at(color.first));
    }
  }

  if (depth_stencil_.has_value()) {
    vk::AttachmentReference depth_stencil_ref;
    depth_stencil_ref.attachment = attachments.size();
    depth_stencil_ref.layout = vk::ImageLayout::eGeneral;
    attachments.push_back(depth_stencil_.value());
  }

  vk::SubpassDescription subpass0;
  subpass0.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
  subpass0.setInputAttachments(color_refs);
  subpass0.setColorAttachments(color_refs);
  subpass0.setResolveAttachments(resolve_refs);
  subpass0.setPDepthStencilAttachment(&depth_stencil_ref);

  vk::SubpassDependency self_dep;
  self_dep.srcSubpass = 0u;  // first subpass
  self_dep.dstSubpass = 0u;  // to itself
  self_dep.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
  self_dep.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
  self_dep.dstStageMask = vk::PipelineStageFlagBits::eFragmentShader;
  self_dep.dstAccessMask = vk::AccessFlagBits::eInputAttachmentRead;
  self_dep.dependencyFlags = vk::DependencyFlagBits::eByRegion;

  vk::RenderPassCreateInfo render_pass_desc;
  render_pass_desc.setAttachments(attachments);
  render_pass_desc.setSubpasses(subpass0);
  render_pass_desc.setDependencies(self_dep);

  auto [result, pass] = device.createRenderPassUnique(render_pass_desc);
  if (result != vk::Result::eSuccess) {
    VALIDATION_LOG << "Failed to create render pass: " << vk::to_string(result);
    return {};
  }
  return std::move(pass);
}

}  // namespace impeller
