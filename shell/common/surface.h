// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_COMMON_SURFACE_H_
#define FLUTTER_SHELL_COMMON_SURFACE_H_

#include <memory>

#include "flutter/flow/compositor_context.h"
#include "flutter/flow/embedded_views.h"
#include "flutter/fml/macros.h"
#include "flutter/shell/common/surface_frame.h"
#include "third_party/skia/include/core/SkCanvas.h"

namespace flutter {

//------------------------------------------------------------------------------
/// @brief      The surface is an abstract representation of an on-screen render
///             target. The client rendering API is completely abstracted away
///             at this level. The implementation of the surface differs based
///             on the client rendering API in use. Currently, the client
///             rendering APIs known to the engine are OpenGL ES, Vulkan,
///             Software & Metal. The `Surface` subclasses for these can be
///             found in the `//flutter/shell/gpu` directory.
///
///             The surface abstractions is one of the most useful features of
///             the rendering subsystem and it allows Flutter to quickly add
///             support for new client rendering APIs.
///
///             Surfaces can be created by the embedder on any thread (but
///             typically the platform task runner). After creation, ownership
///             is transferred over the to rasterizer on the GPU task runner.
///             The rasterizer can own many surfaces during it lifetime but it
///             can only own one surface at a time. When the raster collects the
///             surface, it does so on the GPU task runner (like all rasterizer
///             operation).
///
///
/// @see        `GPUSurfaceGL`, `GPUSurfaceMetal`, `GPUSurfaceVulkan`,
///             `GPUSurfaceSoftware`.
///
class Surface {
 public:
  //----------------------------------------------------------------------------
  /// @brief      Creates a new instance of a surface. Unlike most classes in
  ///             the engine, surfaces may be created on any thread before their
  ///             ownership is transferred over the rasterizer that resides on
  ///             the GPU task runner. Surfaces are typically created by the
  ///             platform view on the platform task runner.
  ///
  Surface();

  //----------------------------------------------------------------------------
  /// @brief      Destroys the surface. Surface owned by the rasterizer are
  ///             destroyed on the GPU task runner in response to the
  ///             `Rasterizer::Teardown` invocation.
  ///
  /// @see        `Rasterizer::Teardown`
  ///
  virtual ~Surface();

  //----------------------------------------------------------------------------
  /// @brief      Determine is a surface is valid. A valid surface must be able
  ///             to vend frames via `Surface::AcquireFrame` and be able to
  ///             submit the same.
  ///
  //  @bug        The rasterizer does not currently do a validity check before
  //              surface frame acquisition.
  ///
  /// @return     `true` if frames may be obtained from the surface for
  ///             subsequent submission back to it.
  ///
  virtual bool IsValid() = 0;

  virtual std::unique_ptr<SurfaceFrame> AcquireFrame(const SkISize& size) = 0;

  virtual SkMatrix GetRootTransformation() const = 0;

  virtual GrContext* GetContext() = 0;

  virtual flutter::ExternalViewEmbedder* GetExternalViewEmbedder();

  virtual bool MakeRenderContextCurrent();

 private:
  FML_DISALLOW_COPY_AND_ASSIGN(Surface);
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_COMMON_SURFACE_H_
