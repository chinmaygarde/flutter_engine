// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "impeller/playground/backend/metal/playground_impl_mtl.h"

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

#include "flutter/fml/mapping.h"
#include "impeller/entity/mtl/entity_shaders.h"
#include "impeller/entity/mtl/framebuffer_blend_shaders.h"
#include "impeller/entity/mtl/modern_shaders.h"
#include "impeller/fixtures/mtl/fixtures_shaders.h"
#include "impeller/playground/imgui/mtl/imgui_shaders.h"
#include "impeller/playground/wsi/glfw/glfw.h"
#include "impeller/renderer/backend/metal/context_mtl.h"
#include "impeller/renderer/backend/metal/formats_mtl.h"
#include "impeller/renderer/backend/metal/surface_mtl.h"
#include "impeller/renderer/backend/metal/texture_mtl.h"
#include "impeller/renderer/mtl/compute_shaders.h"
#include "impeller/scene/shaders/mtl/scene_shaders.h"

namespace impeller {

struct PlaygroundImplMTL::Data {
  CAMetalLayer* metal_layer = nil;
};

static std::vector<std::shared_ptr<fml::Mapping>>
ShaderLibraryMappingsForPlayground() {
  return {std::make_shared<fml::NonOwnedMapping>(
              impeller_entity_shaders_data, impeller_entity_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(
              impeller_modern_shaders_data, impeller_modern_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(
              impeller_framebuffer_blend_shaders_data,
              impeller_framebuffer_blend_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(
              impeller_fixtures_shaders_data, impeller_fixtures_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(impeller_imgui_shaders_data,
                                                 impeller_imgui_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(impeller_scene_shaders_data,
                                                 impeller_scene_shaders_length),
          std::make_shared<fml::NonOwnedMapping>(
              impeller_compute_shaders_data, impeller_compute_shaders_length)

  };
}

PlaygroundImplMTL::PlaygroundImplMTL(PlaygroundSwitches switches,
                                     std::unique_ptr<PlaygroundWindow> window)
    : PlaygroundImpl(switches, std::move(window)),
      data_(std::make_unique<Data>()) {
  auto context = ContextMTL::Create(ShaderLibraryMappingsForPlayground(),
                                    "Playground Library");
  if (!context) {
    return;
  }
  NSWindow* cocoa_window = ::glfwGetCocoaWindow(window);
  if (cocoa_window == nil) {
    return;
  }
  data_->metal_layer = [CAMetalLayer layer];
  data_->metal_layer.device = ContextMTL::Cast(*context).GetMTLDevice();
  data_->metal_layer.pixelFormat =
      ToMTLPixelFormat(context->GetCapabilities()->GetDefaultColorFormat());
  data_->metal_layer.framebufferOnly = NO;
  cocoa_window.contentView.layer = data_->metal_layer;
  cocoa_window.contentView.wantsLayer = YES;

  context_ = std::move(context);
}

PlaygroundImplMTL::~PlaygroundImplMTL() = default;

std::shared_ptr<Context> PlaygroundImplMTL::GetContext() const {
  return context_;
}

// |PlaygroundImpl|
std::unique_ptr<Surface> PlaygroundImplMTL::AcquireSurfaceFrame(
    std::shared_ptr<Context> context) {
  if (!data_->metal_layer) {
    return nullptr;
  }

  const auto layer_size = data_->metal_layer.bounds.size;
  const auto scale = GetContentScale();
  data_->metal_layer.drawableSize =
      CGSizeMake(layer_size.width * scale.x, layer_size.height * scale.y);

  auto drawable =
      SurfaceMTL::GetMetalDrawableAndValidate(context, data_->metal_layer);
  return SurfaceMTL::WrapCurrentMetalLayerDrawable(context, drawable);
}

}  // namespace impeller
