// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_TOOLKIT_INTEROP_IMPELLER_HPP_
#define FLUTTER_IMPELLER_TOOLKIT_INTEROP_IMPELLER_HPP_

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "impeller.h"

#ifndef IMPELLER_HPP_NAMESPACE
#define IMPELLER_HPP_NAMESPACE impeller::hpp
#endif  // IMPELLER_HPP_NAMESPACE

static_assert(IMPELLER_VERSION == IMPELLER_MAKE_VERSION(1, 1, 2, 0),
              "C++ bindings must be for the same version as the C API.");

namespace IMPELLER_HPP_NAMESPACE {

template <class T>
struct Proc {
  using FunctionType = T;

  const char* name = nullptr;

  FunctionType* function = nullptr;

  template <class... Args>
  auto operator()(Args&&... args) const {
    return function(std::forward<Args>(args)...);
  }
};

#define IMPELLER_HPP_EACH_PROC(PROC)                        \
  PROC(ImpellerColorFilterCreateBlendNew)                   \
  PROC(ImpellerColorFilterCreateColorMatrixNew)             \
  PROC(ImpellerColorFilterRelease)                          \
  PROC(ImpellerColorFilterRetain)                           \
  PROC(ImpellerColorSourceCreateConicalGradientNew)         \
  PROC(ImpellerColorSourceCreateImageNew)                   \
  PROC(ImpellerColorSourceCreateLinearGradientNew)          \
  PROC(ImpellerColorSourceCreateRadialGradientNew)          \
  PROC(ImpellerColorSourceCreateSweepGradientNew)           \
  PROC(ImpellerColorSourceRelease)                          \
  PROC(ImpellerColorSourceRetain)                           \
  PROC(ImpellerContextCreateOpenGLESNew)                    \
  PROC(ImpellerContextRelease)                              \
  PROC(ImpellerContextRetain)                               \
  PROC(ImpellerDisplayListBuilderClipOval)                  \
  PROC(ImpellerDisplayListBuilderClipPath)                  \
  PROC(ImpellerDisplayListBuilderClipRect)                  \
  PROC(ImpellerDisplayListBuilderClipRoundedRect)           \
  PROC(ImpellerDisplayListBuilderCreateDisplayListNew)      \
  PROC(ImpellerDisplayListBuilderDrawDashedLine)            \
  PROC(ImpellerDisplayListBuilderDrawDisplayList)           \
  PROC(ImpellerDisplayListBuilderDrawLine)                  \
  PROC(ImpellerDisplayListBuilderDrawOval)                  \
  PROC(ImpellerDisplayListBuilderDrawPaint)                 \
  PROC(ImpellerDisplayListBuilderDrawParagraph)             \
  PROC(ImpellerDisplayListBuilderDrawPath)                  \
  PROC(ImpellerDisplayListBuilderDrawRect)                  \
  PROC(ImpellerDisplayListBuilderDrawRoundedRect)           \
  PROC(ImpellerDisplayListBuilderDrawRoundedRectDifference) \
  PROC(ImpellerDisplayListBuilderDrawTexture)               \
  PROC(ImpellerDisplayListBuilderDrawTextureRect)           \
  PROC(ImpellerDisplayListBuilderGetSaveCount)              \
  PROC(ImpellerDisplayListBuilderGetTransform)              \
  PROC(ImpellerDisplayListBuilderNew)                       \
  PROC(ImpellerDisplayListBuilderRelease)                   \
  PROC(ImpellerDisplayListBuilderResetTransform)            \
  PROC(ImpellerDisplayListBuilderRestore)                   \
  PROC(ImpellerDisplayListBuilderRestoreToCount)            \
  PROC(ImpellerDisplayListBuilderRetain)                    \
  PROC(ImpellerDisplayListBuilderRotate)                    \
  PROC(ImpellerDisplayListBuilderSave)                      \
  PROC(ImpellerDisplayListBuilderSaveLayer)                 \
  PROC(ImpellerDisplayListBuilderScale)                     \
  PROC(ImpellerDisplayListBuilderSetTransform)              \
  PROC(ImpellerDisplayListBuilderTransform)                 \
  PROC(ImpellerDisplayListBuilderTranslate)                 \
  PROC(ImpellerDisplayListRelease)                          \
  PROC(ImpellerDisplayListRetain)                           \
  PROC(ImpellerGetVersion)                                  \
  PROC(ImpellerImageFilterCreateBlurNew)                    \
  PROC(ImpellerImageFilterCreateComposeNew)                 \
  PROC(ImpellerImageFilterCreateDilateNew)                  \
  PROC(ImpellerImageFilterCreateErodeNew)                   \
  PROC(ImpellerImageFilterCreateMatrixNew)                  \
  PROC(ImpellerImageFilterRelease)                          \
  PROC(ImpellerImageFilterRetain)                           \
  PROC(ImpellerMaskFilterCreateBlurNew)                     \
  PROC(ImpellerMaskFilterRelease)                           \
  PROC(ImpellerMaskFilterRetain)                            \
  PROC(ImpellerPaintNew)                                    \
  PROC(ImpellerPaintRelease)                                \
  PROC(ImpellerPaintRetain)                                 \
  PROC(ImpellerPaintSetBlendMode)                           \
  PROC(ImpellerPaintSetColor)                               \
  PROC(ImpellerPaintSetColorFilter)                         \
  PROC(ImpellerPaintSetColorSource)                         \
  PROC(ImpellerPaintSetDrawStyle)                           \
  PROC(ImpellerPaintSetImageFilter)                         \
  PROC(ImpellerPaintSetMaskFilter)                          \
  PROC(ImpellerPaintSetStrokeCap)                           \
  PROC(ImpellerPaintSetStrokeJoin)                          \
  PROC(ImpellerPaintSetStrokeMiter)                         \
  PROC(ImpellerPaintSetStrokeWidth)                         \
  PROC(ImpellerParagraphBuilderAddText)                     \
  PROC(ImpellerParagraphBuilderBuildParagraphNew)           \
  PROC(ImpellerParagraphBuilderNew)                         \
  PROC(ImpellerParagraphBuilderPopStyle)                    \
  PROC(ImpellerParagraphBuilderPushStyle)                   \
  PROC(ImpellerParagraphBuilderRelease)                     \
  PROC(ImpellerParagraphBuilderRetain)                      \
  PROC(ImpellerParagraphGetAlphabeticBaseline)              \
  PROC(ImpellerParagraphGetHeight)                          \
  PROC(ImpellerParagraphGetIdeographicBaseline)             \
  PROC(ImpellerParagraphGetLineCount)                       \
  PROC(ImpellerParagraphGetLongestLineWidth)                \
  PROC(ImpellerParagraphGetMaxIntrinsicWidth)               \
  PROC(ImpellerParagraphGetMaxWidth)                        \
  PROC(ImpellerParagraphGetMinIntrinsicWidth)               \
  PROC(ImpellerParagraphRelease)                            \
  PROC(ImpellerParagraphRetain)                             \
  PROC(ImpellerParagraphStyleNew)                           \
  PROC(ImpellerParagraphStyleRelease)                       \
  PROC(ImpellerParagraphStyleRetain)                        \
  PROC(ImpellerParagraphStyleSetBackground)                 \
  PROC(ImpellerParagraphStyleSetFontFamily)                 \
  PROC(ImpellerParagraphStyleSetFontSize)                   \
  PROC(ImpellerParagraphStyleSetFontStyle)                  \
  PROC(ImpellerParagraphStyleSetFontWeight)                 \
  PROC(ImpellerParagraphStyleSetForeground)                 \
  PROC(ImpellerParagraphStyleSetHeight)                     \
  PROC(ImpellerParagraphStyleSetLocale)                     \
  PROC(ImpellerParagraphStyleSetMaxLines)                   \
  PROC(ImpellerParagraphStyleSetTextAlignment)              \
  PROC(ImpellerParagraphStyleSetTextDirection)              \
  PROC(ImpellerPathBuilderAddArc)                           \
  PROC(ImpellerPathBuilderAddOval)                          \
  PROC(ImpellerPathBuilderAddRect)                          \
  PROC(ImpellerPathBuilderAddRoundedRect)                   \
  PROC(ImpellerPathBuilderClose)                            \
  PROC(ImpellerPathBuilderCopyPathNew)                      \
  PROC(ImpellerPathBuilderCubicCurveTo)                     \
  PROC(ImpellerPathBuilderLineTo)                           \
  PROC(ImpellerPathBuilderMoveTo)                           \
  PROC(ImpellerPathBuilderNew)                              \
  PROC(ImpellerPathBuilderQuadraticCurveTo)                 \
  PROC(ImpellerPathBuilderRelease)                          \
  PROC(ImpellerPathBuilderRetain)                           \
  PROC(ImpellerPathBuilderTakePathNew)                      \
  PROC(ImpellerPathRelease)                                 \
  PROC(ImpellerPathRetain)                                  \
  PROC(ImpellerSurfaceCreateWrappedFBONew)                  \
  PROC(ImpellerSurfaceDrawDisplayList)                      \
  PROC(ImpellerSurfaceRelease)                              \
  PROC(ImpellerSurfaceRetain)                               \
  PROC(ImpellerTextureCreateWithContentsNew)                \
  PROC(ImpellerTextureCreateWithOpenGLTextureHandleNew)     \
  PROC(ImpellerTextureGetOpenGLHandle)                      \
  PROC(ImpellerTextureRelease)                              \
  PROC(ImpellerTextureRetain)                               \
  PROC(ImpellerTypographyContextNew)                        \
  PROC(ImpellerTypographyContextRegisterFont)               \
  PROC(ImpellerTypographyContextRelease)                    \
  PROC(ImpellerTypographyContextRetain)

struct ProcTable {
  bool Initialize(std::function<void*(const char* function_name)> resolver) {
#define IMPELLER_HPP_PROC(proc)                                         \
  {                                                                     \
    proc.function =                                                     \
        reinterpret_cast<decltype(proc.function)>(resolver(proc.name)); \
    if (proc.function == nullptr) {                                     \
      return false;                                                     \
    }                                                                   \
  }
    IMPELLER_HPP_EACH_PROC(IMPELLER_HPP_PROC)
#undef IMPELLER_HPP_PROC
    return true;
  }

#define IMPELLER_HPP_PROC(name) Proc<decltype(name)> name = {#name, nullptr};
  IMPELLER_HPP_EACH_PROC(IMPELLER_HPP_PROC)
#undef IMPELLER_HPP_PROC
};

extern ProcTable gGlobalProcTable;

enum class AdoptTag {
  kAdopt,
};

template <class T, class Traits>
class Object {
 public:
  Object() = default;

  Object(T object) { Reset(object); }

  Object(T object, AdoptTag) : object_(object) {}

  ~Object() { Reset(); }

  Object(Object&& other) { std::swap(object_, other.object_); }

  Object(const Object& other) { Reset(other.Get()); }

  Object& operator=(Object&& other) {
    std::swap(object_, other.object_);
    return *this;
  }

  Object& operator=(const Object& other) {
    Reset(other.Get());
    return *this;
  }

  T Get() const { return object_; }

  explicit operator bool() const { return object_ != nullptr; }

 private:
  T object_ = nullptr;

  void Reset(T other = nullptr) {
    if (object_ == other) {
      return;
    }
    if (object_) {
      Traits::Release(object_);
      object_ = nullptr;
    }
    if (other) {
      Traits::Retain(other);
      object_ = other;
    }
  }

  [[nodiscard]] T Leak() {
    T result = object_;
    object_ = nullptr;
    return result;
  }
};

#define IMPELLER_HPP_DEFINE_TRAITS(object)   \
  struct object##Traits {                    \
    static void Retain(object ctx) {         \
      gGlobalProcTable.object##Retain(ctx);  \
    }                                        \
    static void Release(object ctx) {        \
      gGlobalProcTable.object##Release(ctx); \
    }                                        \
  };

IMPELLER_HPP_DEFINE_TRAITS(ImpellerColorFilter);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerColorSource);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerContext);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerDisplayList);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerDisplayListBuilder);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerImageFilter);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerMaskFilter);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerPaint);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerParagraph);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerParagraphBuilder);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerParagraphStyle);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerPath);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerPathBuilder);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerSurface);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerTexture);
IMPELLER_HPP_DEFINE_TRAITS(ImpellerTypographyContext);

#undef IMPELLER_HPP_DEFINE_TRAITS

class Mapping final {
 public:
  Mapping(const uint8_t* mapping,
          size_t size,
          std::function<void()> release_callback)
      : mapping_(mapping),
        size_(size),
        release_callback_(std::move(release_callback)) {}

  const uint8_t* GetMapping() const { return mapping_; }

  size_t GetSize() const { return size_; }

 private:
  const uint8_t* mapping_ = nullptr;
  size_t size_ = 0u;
  std::function<void()> release_callback_;
};

class Context final : public Object<ImpellerContext, ImpellerContextTraits> {
 public:
  Context(ImpellerContext context, AdoptTag tag) : Object(context, tag) {}

  static Context OpenGLES(
      std::function<void*(const char*)> gl_proc_address_resolver) {
    struct UserData {
      std::function<void*(const char*)> resolver;
    };
    UserData user_data;
    user_data.resolver = gl_proc_address_resolver;
    ImpellerProcAddressCallback callback = [](const char* proc_name,
                                              void* user_data) -> void* {
      return reinterpret_cast<UserData*>(user_data)->resolver(proc_name);
    };
    return Context(
        gGlobalProcTable.ImpellerContextCreateOpenGLESNew(IMPELLER_VERSION,  //
                                                          callback,          //
                                                          &user_data         //
                                                          ),
        AdoptTag::kAdopt);
  }
};

class Texture final : public Object<ImpellerTexture, ImpellerTextureTraits> {
 public:
  Texture(ImpellerTexture texture, AdoptTag adopt) : Object(texture, adopt) {}

  static Texture WithContents(const Context& context,
                              const ImpellerTextureDescriptor& descriptor,
                              std::unique_ptr<Mapping> mapping = nullptr) {
    if (mapping == nullptr) {
      mapping = std::make_unique<Mapping>(nullptr, 0u, nullptr);
    }
    ImpellerMapping c_mapping = {};
    c_mapping.data = mapping->GetMapping();
    c_mapping.length = mapping->GetSize();
    c_mapping.on_release = [](void* user_data) -> void {
      delete reinterpret_cast<Mapping*>(user_data);
    };
    return Texture(gGlobalProcTable.ImpellerTextureCreateWithContentsNew(
                       context.Get(),     //
                       &descriptor,       //
                       &c_mapping,        //
                       mapping.release()  //
                       ),
                   AdoptTag::kAdopt);
  }

  static Texture WithOpenGLTexture(const Context& context,
                                   const ImpellerTextureDescriptor& descriptor,
                                   uint64_t handle) {
    return Texture(
        gGlobalProcTable.ImpellerTextureCreateWithOpenGLTextureHandleNew(
            context.Get(),  //
            &descriptor,    //
            handle          //
            ),
        AdoptTag::kAdopt);
  }

  uint64_t GetOpenGLHandle() const {
    return gGlobalProcTable.ImpellerTextureGetOpenGLHandle(Get());
  }
};

class ColorFilter final
    : public Object<ImpellerColorFilter, ImpellerColorFilterTraits> {
 public:
  ColorFilter(ImpellerColorFilter filter, AdoptTag tag) : Object(filter, tag) {}

  static ColorFilter Blend(const ImpellerColor& color, ImpellerBlendMode mode) {
    return ColorFilter(
        gGlobalProcTable.ImpellerColorFilterCreateBlendNew(&color, mode),
        AdoptTag::kAdopt);
  }

  static ColorFilter Matrix(const ImpellerColorMatrix& color_matrix) {
    return ColorFilter(
        gGlobalProcTable.ImpellerColorFilterCreateColorMatrixNew(&color_matrix),
        AdoptTag::kAdopt);
  }
};

class ColorSource final
    : public Object<ImpellerColorSource, ImpellerColorSourceTraits> {
 public:
  ColorSource(ImpellerColorSource source, AdoptTag tag) : Object(source, tag) {}

  static ColorSource ConicalGradient(
      const ImpellerPoint& start_center,
      float start_radius,
      const ImpellerPoint& end_center,
      float end_radius,
      uint32_t stop_count,
      const ImpellerColor* colors,
      const float* stops,
      ImpellerTileMode tile_mode,
      const ImpellerMatrix* transformation = nullptr) {
    return ColorSource(
        gGlobalProcTable.ImpellerColorSourceCreateConicalGradientNew(
            &start_center,  //
            start_radius,   //
            &end_center,    //
            end_radius,     //
            stop_count,     //
            colors,         //
            stops,          //
            tile_mode,      //
            transformation  //
            ),
        AdoptTag::kAdopt);
  }

  static ColorSource Image(const Texture& image,
                           ImpellerTileMode horizontal_tile_mode,
                           ImpellerTileMode vertical_tile_mode,
                           ImpellerTextureSampling sampling,
                           const ImpellerMatrix* transformation = nullptr) {
    return ColorSource(gGlobalProcTable.ImpellerColorSourceCreateImageNew(
                           image.Get(),           //
                           horizontal_tile_mode,  //
                           vertical_tile_mode,    //
                           sampling,              //
                           transformation         //
                           ),
                       AdoptTag::kAdopt);
  }

  static ColorSource LinearGradient(
      const ImpellerPoint& start_point,
      const ImpellerPoint& end_point,
      uint32_t stop_count,
      const ImpellerColor* colors,
      const float* stops,
      ImpellerTileMode tile_mode,
      const ImpellerMatrix* transformation = nullptr) {
    return ColorSource(
        gGlobalProcTable.ImpellerColorSourceCreateLinearGradientNew(
            &start_point,
            &end_point,     //
            stop_count,     //
            colors,         //
            stops,          //
            tile_mode,      //
            transformation  //
            ),
        AdoptTag::kAdopt);
  }

  static ColorSource RadialGradient(
      const ImpellerPoint& center,
      float radius,
      uint32_t stop_count,
      const ImpellerColor* colors,
      const float* stops,
      ImpellerTileMode tile_mode,
      const ImpellerMatrix* transformation = nullptr) {
    return ColorSource(
        gGlobalProcTable.ImpellerColorSourceCreateRadialGradientNew(
            &center,        //
            radius,         //
            stop_count,     //
            colors,         //
            stops,          //
            tile_mode,      //
            transformation  //
            ),
        AdoptTag::kAdopt);
  }

  static ColorSource SweepGradient(
      const ImpellerPoint& center,
      float start,
      float end,
      uint32_t stop_count,
      const ImpellerColor* colors,
      const float* stops,
      ImpellerTileMode tile_mode,
      const ImpellerMatrix* transformation = nullptr) {
    return ColorSource(
        gGlobalProcTable.ImpellerColorSourceCreateSweepGradientNew(
            &center,        //
            start,          //
            end,            //
            stop_count,     //
            colors,         //
            stops,          //
            tile_mode,      //
            transformation  //
            ),
        AdoptTag::kAdopt);
  }
};

class ImageFilter final
    : public Object<ImpellerImageFilter, ImpellerImageFilterTraits> {
 public:
  ImageFilter(ImpellerImageFilter filter, AdoptTag tag) : Object(filter, tag) {}

  static ImageFilter Blur(float x_sigma,
                          float y_sigma,
                          ImpellerTileMode tile_mode) {
    return ImageFilter(gGlobalProcTable.ImpellerImageFilterCreateBlurNew(
                           x_sigma, y_sigma, tile_mode),
                       AdoptTag::kAdopt);
  }

  static ImageFilter Compose(const ImageFilter& outer,
                             const ImageFilter& inner) {
    return ImageFilter(gGlobalProcTable.ImpellerImageFilterCreateComposeNew(
                           outer.Get(), inner.Get()),
                       AdoptTag::kAdopt);
  }

  static ImageFilter Dilate(float x_radius, float y_radius) {
    return ImageFilter(
        gGlobalProcTable.ImpellerImageFilterCreateDilateNew(x_radius, y_radius),
        AdoptTag::kAdopt);
  }

  static ImageFilter Erode(float x_radius, float y_radius) {
    return ImageFilter(
        gGlobalProcTable.ImpellerImageFilterCreateErodeNew(x_radius, y_radius),
        AdoptTag::kAdopt);
  }

  static ImageFilter Matrix(const ImpellerMatrix& matrix,
                            ImpellerTextureSampling sampling) {
    return ImageFilter(
        gGlobalProcTable.ImpellerImageFilterCreateMatrixNew(&matrix, sampling),
        AdoptTag::kAdopt);
  }
};

class MaskFilter final
    : public Object<ImpellerMaskFilter, ImpellerMaskFilterTraits> {
 public:
  MaskFilter(ImpellerMaskFilter filter, AdoptTag tag) : Object(filter, tag) {}

  static MaskFilter Blur(ImpellerBlurStyle style, float sigma) {
    return MaskFilter(
        gGlobalProcTable.ImpellerMaskFilterCreateBlurNew(style, sigma),
        AdoptTag::kAdopt);
  }
};

class Paragraph final
    : public Object<ImpellerParagraph, ImpellerParagraphTraits> {
 public:
  Paragraph(ImpellerParagraph paragraph, AdoptTag tag)
      : Object(paragraph, AdoptTag::kAdopt) {}

  float GetAlphabeticBaseline() {
    return gGlobalProcTable.ImpellerParagraphGetAlphabeticBaseline(Get());
  }

  float GetHeight() {
    return gGlobalProcTable.ImpellerParagraphGetHeight(Get());
  }

  float GetIdeographicBaseline() {
    return gGlobalProcTable.ImpellerParagraphGetIdeographicBaseline(Get());
  }

  uint32_t GetLineCount() {
    return gGlobalProcTable.ImpellerParagraphGetLineCount(Get());
  }

  float GetLongestLineWidth() {
    return gGlobalProcTable.ImpellerParagraphGetLongestLineWidth(Get());
  }

  float GetMaxIntrinsicWidth() {
    return gGlobalProcTable.ImpellerParagraphGetMaxIntrinsicWidth(Get());
  }

  float GetMaxWidth() {
    return gGlobalProcTable.ImpellerParagraphGetMaxWidth(Get());
  }

  float GetMinIntrinsicWidth() {
    return gGlobalProcTable.ImpellerParagraphGetMinIntrinsicWidth(Get());
  }
};

class Paint final : public Object<ImpellerPaint, ImpellerPaintTraits> {
 public:
  Paint() : Object(gGlobalProcTable.ImpellerPaintNew(), AdoptTag::kAdopt) {}

  Paint& SetColor(const ImpellerColor& color) {
    gGlobalProcTable.ImpellerPaintSetColor(Get(), &color);
    return *this;
  }

  Paint& SetBlendMode(ImpellerBlendMode mode) {
    gGlobalProcTable.ImpellerPaintSetBlendMode(Get(), mode);
    return *this;
  }

  Paint& SetDrawStyle(ImpellerDrawStyle style) {
    gGlobalProcTable.ImpellerPaintSetDrawStyle(Get(), style);
    return *this;
  }

  Paint& SetStrokeCap(ImpellerStrokeCap cap) {
    gGlobalProcTable.ImpellerPaintSetStrokeCap(Get(), cap);
    return *this;
  }

  Paint& SetStrokeJoin(ImpellerStrokeJoin join) {
    gGlobalProcTable.ImpellerPaintSetStrokeJoin(Get(), join);
    return *this;
  }

  Paint& SetStrokeWidth(float width) {
    gGlobalProcTable.ImpellerPaintSetStrokeWidth(Get(), width);
    return *this;
  }

  Paint& SetStrokeMiter(float miter) {
    gGlobalProcTable.ImpellerPaintSetStrokeMiter(Get(), miter);
    return *this;
  }

  Paint& SetColorFilter(const ColorFilter& filter) {
    gGlobalProcTable.ImpellerPaintSetColorFilter(Get(), filter.Get());
    return *this;
  }

  Paint& SetColorSource(const ColorSource& source) {
    gGlobalProcTable.ImpellerPaintSetColorSource(Get(), source.Get());
    return *this;
  }

  Paint& SetImageFilter(const ImageFilter& filter) {
    gGlobalProcTable.ImpellerPaintSetImageFilter(Get(), filter.Get());
    return *this;
  }

  Paint& SetMaskFilter(const MaskFilter& filter) {
    gGlobalProcTable.ImpellerPaintSetMaskFilter(Get(), filter.Get());
    return *this;
  }
};

class ParagraphStyle final
    : public Object<ImpellerParagraphStyle, ImpellerParagraphStyleTraits> {
 public:
  ParagraphStyle()
      : Object(gGlobalProcTable.ImpellerParagraphStyleNew(), AdoptTag::kAdopt) {
  }

  ParagraphStyle& SetBackground(const Paint& paint) {
    gGlobalProcTable.ImpellerParagraphStyleSetBackground(Get(), paint.Get());
    return *this;
  }

  ParagraphStyle& SetFontFamily(const char* family_name) {
    gGlobalProcTable.ImpellerParagraphStyleSetFontFamily(Get(), family_name);
    return *this;
  }

  ParagraphStyle& SetFontSize(float size) {
    gGlobalProcTable.ImpellerParagraphStyleSetFontSize(Get(), size);
    return *this;
  }

  ParagraphStyle& SetFontStyle(ImpellerFontStyle style) {
    gGlobalProcTable.ImpellerParagraphStyleSetFontStyle(Get(), style);
    return *this;
  }

  ParagraphStyle& SetFontWeight(ImpellerFontWeight weight) {
    gGlobalProcTable.ImpellerParagraphStyleSetFontWeight(Get(), weight);
    return *this;
  }

  ParagraphStyle& SetForeground(const Paint& paint) {
    gGlobalProcTable.ImpellerParagraphStyleSetForeground(Get(), paint.Get());
    return *this;
  }

  ParagraphStyle& SetHeight(float height) {
    gGlobalProcTable.ImpellerParagraphStyleSetHeight(Get(), height);
    return *this;
  }

  ParagraphStyle& SetLocale(const char* locale) {
    gGlobalProcTable.ImpellerParagraphStyleSetLocale(Get(), locale);
    return *this;
  }

  ParagraphStyle& SetMaxLines(uint32_t max_lines) {
    gGlobalProcTable.ImpellerParagraphStyleSetMaxLines(Get(), max_lines);
    return *this;
  }

  ParagraphStyle& SetTextAlignment(ImpellerTextAlignment align) {
    gGlobalProcTable.ImpellerParagraphStyleSetTextAlignment(Get(), align);
    return *this;
  }

  ParagraphStyle& SetTextDirection(ImpellerTextDirection direction) {
    gGlobalProcTable.ImpellerParagraphStyleSetTextDirection(Get(), direction);
    return *this;
  }
};

class TypographyContext final : public Object<ImpellerTypographyContext,
                                              ImpellerTypographyContextTraits> {
 public:
  TypographyContext()
      : Object(gGlobalProcTable.ImpellerTypographyContextNew(),
               AdoptTag::kAdopt) {}

  bool RegisterFont(std::unique_ptr<Mapping> mapping,
                    const char* optional_family_name_alias = nullptr) {
    if (!mapping) {
      return false;
    }
    ImpellerMapping c_mapping = {};
    c_mapping.data = mapping->GetMapping();
    c_mapping.length = mapping->GetSize();
    c_mapping.on_release = [](void* user_data) {
      delete reinterpret_cast<Mapping*>(user_data);
    };
    return gGlobalProcTable.ImpellerTypographyContextRegisterFont(
        Get(),                      //
        &c_mapping,                 //
        mapping.release(),          //
        optional_family_name_alias  //
    );
  }
};

class ParagraphBuilder final
    : public Object<ImpellerParagraphBuilder, ImpellerParagraphBuilderTraits> {
 public:
  ParagraphBuilder(const TypographyContext& context)
      : Object(gGlobalProcTable.ImpellerParagraphBuilderNew(context.Get()),
               AdoptTag::kAdopt) {}

  Paragraph Build(float width) {
    return Paragraph(
        gGlobalProcTable.ImpellerParagraphBuilderBuildParagraphNew(Get(),  //
                                                                   width   //
                                                                   ),
        AdoptTag::kAdopt);
  }

  ParagraphBuilder& PushStyle(const ParagraphStyle& style) {
    gGlobalProcTable.ImpellerParagraphBuilderPushStyle(Get(), style.Get());
    return *this;
  }

  ParagraphBuilder& PopStyle() {
    gGlobalProcTable.ImpellerParagraphBuilderPopStyle(Get());
    return *this;
  }

  ParagraphBuilder& AddText(const uint8_t* utf8_data, uint32_t length) {
    gGlobalProcTable.ImpellerParagraphBuilderAddText(Get(), utf8_data, length);
    return *this;
  }

  ParagraphBuilder& AddText(const std::string& string) {
    return AddText(reinterpret_cast<const uint8_t*>(string.data()),
                   string.size());
  }

  ParagraphBuilder& AddText(const std::string_view& string) {
    return AddText(reinterpret_cast<const uint8_t*>(string.data()),
                   string.size());
  }
};

class Path final : public Object<ImpellerPath, ImpellerPathTraits> {
 public:
  Path(ImpellerPath path, AdoptTag tag) : Object(path, tag) {}
};

class PathBuilder final
    : public Object<ImpellerPathBuilder, ImpellerPathBuilderTraits> {
 public:
  PathBuilder()
      : Object(gGlobalProcTable.ImpellerPathBuilderNew(), AdoptTag::kAdopt) {}

  Path BuildCopy(ImpellerFillType fill) const {
    return Path(gGlobalProcTable.ImpellerPathBuilderCopyPathNew(Get(), fill),
                AdoptTag::kAdopt);
  }

  Path Build(ImpellerFillType fill) {
    return Path(gGlobalProcTable.ImpellerPathBuilderTakePathNew(Get(), fill),
                AdoptTag::kAdopt);
  }

  PathBuilder& AddArc(const ImpellerRect& oval_bounds,
                      float start_angle_degrees,
                      float end_angle_degrees) {
    gGlobalProcTable.ImpellerPathBuilderAddArc(Get(),                //
                                               &oval_bounds,         //
                                               start_angle_degrees,  //
                                               end_angle_degrees     //
    );
    return *this;
  }

  PathBuilder& AddOval(const ImpellerRect& oval_bounds) {
    gGlobalProcTable.ImpellerPathBuilderAddOval(Get(), &oval_bounds);
    return *this;
  }

  PathBuilder& AddRect(const ImpellerRect& rect) {
    gGlobalProcTable.ImpellerPathBuilderAddRect(Get(), &rect);
    return *this;
  }

  PathBuilder& AddRoundedRect(const ImpellerRect& rect,
                              const ImpellerRoundingRadii& rounding_radii) {
    gGlobalProcTable.ImpellerPathBuilderAddRoundedRect(Get(), &rect,
                                                       &rounding_radii);
    return *this;
  }

  PathBuilder& Close() {
    gGlobalProcTable.ImpellerPathBuilderClose(Get());
    return *this;
  }

  PathBuilder& CubicCurveTo(const ImpellerPoint& control_point_1,
                            const ImpellerPoint& control_point_2,
                            const ImpellerPoint& end_point) {
    gGlobalProcTable.ImpellerPathBuilderCubicCurveTo(
        Get(), &control_point_1, &control_point_2, &end_point);
    return *this;
  }

  PathBuilder& LineTo(const ImpellerPoint& location) {
    gGlobalProcTable.ImpellerPathBuilderLineTo(Get(), &location);
    return *this;
  }

  PathBuilder& MoveTo(const ImpellerPoint& location) {
    gGlobalProcTable.ImpellerPathBuilderMoveTo(Get(), &location);
    return *this;
  }

  PathBuilder& QuadraticCurveTo(const ImpellerPoint& control_point,
                                const ImpellerPoint& end_point) {
    gGlobalProcTable.ImpellerPathBuilderQuadraticCurveTo(Get(), &control_point,
                                                         &end_point);
    return *this;
  }
};

class DisplayList final
    : public Object<ImpellerDisplayList, ImpellerDisplayListTraits> {
 public:
  DisplayList(ImpellerDisplayList display_list, AdoptTag tag)
      : Object(display_list, tag) {}
};

class Surface final : public Object<ImpellerSurface, ImpellerSurfaceTraits> {
 public:
  Surface(ImpellerSurface surface) : Object(surface) {}

  Surface(ImpellerSurface surface, AdoptTag tag) : Object(surface, tag) {}

  static Surface WrapFBO(const Context& context,
                         uint64_t fbo,
                         ImpellerPixelFormat format,
                         const ImpellerISize& size) {
    return Surface(
        gGlobalProcTable.ImpellerSurfaceCreateWrappedFBONew(context.Get(),  //
                                                            fbo,            //
                                                            format,         //
                                                            &size           //
                                                            ),
        AdoptTag::kAdopt);
  }

  bool Draw(const DisplayList& display_list) {
    return gGlobalProcTable.ImpellerSurfaceDrawDisplayList(Get(),
                                                           display_list.Get());
  }
};

class DisplayListBuilder final
    : public Object<ImpellerDisplayListBuilder,
                    ImpellerDisplayListBuilderTraits> {
 public:
  DisplayListBuilder(const ImpellerRect* cull_rect = nullptr)
      : Object(gGlobalProcTable.ImpellerDisplayListBuilderNew(cull_rect),
               AdoptTag::kAdopt) {}

  DisplayList Build() {
    return DisplayList(
        gGlobalProcTable.ImpellerDisplayListBuilderCreateDisplayListNew(Get()),
        AdoptTag::kAdopt);
  }

  DisplayListBuilder& ClipOval(const ImpellerRect& oval_bounds,
                               ImpellerClipOperation op) {
    gGlobalProcTable.ImpellerDisplayListBuilderClipOval(Get(),         //
                                                        &oval_bounds,  //
                                                        op);
    return *this;
  }

  DisplayListBuilder& ClipPath(const Path& path, ImpellerClipOperation op) {
    gGlobalProcTable.ImpellerDisplayListBuilderClipPath(Get(),       //
                                                        path.Get(),  //
                                                        op);
    return *this;
  }

  DisplayListBuilder& ClipRect(const ImpellerRect& rect,
                               ImpellerClipOperation op) {
    gGlobalProcTable.ImpellerDisplayListBuilderClipRect(Get(),  //
                                                        &rect,  //
                                                        op);
    return *this;
  }

  DisplayListBuilder& ClipRoundedRect(const ImpellerRect& rect,
                                      const ImpellerRoundingRadii& radii,
                                      ImpellerClipOperation op) {
    gGlobalProcTable.ImpellerDisplayListBuilderClipRoundedRect(Get(),   //
                                                               &rect,   //
                                                               &radii,  //
                                                               op       //
    );
    return *this;
  }

  DisplayListBuilder& DrawDashedLine(const ImpellerPoint& from,
                                     const ImpellerPoint& to,
                                     float on_length,
                                     float off_length,
                                     const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawDashedLine(Get(),       //
                                                              &from,       //
                                                              &to,         //
                                                              on_length,   //
                                                              off_length,  //
                                                              paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawDisplayList(const DisplayList& display_list,
                                      float opacity = 1.0f) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawDisplayList(
        Get(), display_list.Get(), opacity);
    return *this;
  }

  DisplayListBuilder& DrawLine(const ImpellerPoint& from,
                               const ImpellerPoint& to,
                               const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawLine(Get(),       //
                                                        &from,       //
                                                        &to,         //
                                                        paint.Get()  //
    );
    return *this;
  }

  DisplayListBuilder& DrawOval(const ImpellerRect& oval_bounds,
                               const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawOval(Get(),         //
                                                        &oval_bounds,  //
                                                        paint.Get()    //
    );
    return *this;
  }

  DisplayListBuilder& DrawPaint(const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawPaint(Get(), paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawParagraph(const Paragraph& paragraph,
                                    const ImpellerPoint& point) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawParagraph(
        Get(), paragraph.Get(), &point);
    return *this;
  }

  DisplayListBuilder& DrawPath(const Path& path, const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawPath(Get(), path.Get(),
                                                        paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawRect(const ImpellerRect& rect, const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawRect(Get(), &rect,
                                                        paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawRoundedRect(const ImpellerRect& rect,
                                      const ImpellerRoundingRadii& radii,
                                      const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawRoundedRect(Get(),   //
                                                               &rect,   //
                                                               &radii,  //
                                                               paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawRoundedRectDifference(
      const ImpellerRect& outer_rect,
      const ImpellerRoundingRadii& outer_radii,
      const ImpellerRect& inner_rect,
      const ImpellerRoundingRadii& inner_radii,
      const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawRoundedRectDifference(
        Get(),         //
        &outer_rect,   //
        &outer_radii,  //
        &inner_rect,   //
        &inner_radii,  //
        paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawTexture(const Texture& texture,
                                  const ImpellerPoint& point,
                                  ImpellerTextureSampling sampling,
                                  const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawTexture(
        Get(), texture.Get(), &point, sampling, paint.Get());
    return *this;
  }

  DisplayListBuilder& DrawTextureRect(const Texture& texture,
                                      const ImpellerRect& src_rect,
                                      const ImpellerRect& dst_rect,
                                      ImpellerTextureSampling sampling,
                                      const Paint& paint) {
    gGlobalProcTable.ImpellerDisplayListBuilderDrawTextureRect(
        Get(), texture.Get(),  //
        &src_rect,             //
        &dst_rect,             //
        sampling,              //
        paint.Get());
    return *this;
  }

  uint32_t GetSaveCount() {
    return gGlobalProcTable.ImpellerDisplayListBuilderGetSaveCount(Get());
  }

  ImpellerMatrix GetTransform() {
    ImpellerMatrix result;
    gGlobalProcTable.ImpellerDisplayListBuilderGetTransform(Get(), &result);
    return result;
  }

  DisplayListBuilder& ResetTransform() {
    gGlobalProcTable.ImpellerDisplayListBuilderResetTransform(Get());
    return *this;
  }

  DisplayListBuilder& Restore() {
    gGlobalProcTable.ImpellerDisplayListBuilderRestore(Get());
    return *this;
  }

  DisplayListBuilder& RestoreToCount(uint32_t count) {
    gGlobalProcTable.ImpellerDisplayListBuilderRestoreToCount(Get(),  //
                                                              count);
    return *this;
  }

  DisplayListBuilder& Rotate(float angle_degrees) {
    gGlobalProcTable.ImpellerDisplayListBuilderRotate(Get(),  //
                                                      angle_degrees);
    return *this;
  }

  DisplayListBuilder& Save() {
    gGlobalProcTable.ImpellerDisplayListBuilderSave(Get());
    return *this;
  }

  DisplayListBuilder& SaveLayer(const ImpellerRect& bounds,
                                const Paint* paint = nullptr,
                                const ImageFilter* backdrop = nullptr) {
    gGlobalProcTable.ImpellerDisplayListBuilderSaveLayer(
        Get(),                             //
        &bounds,                           //
        paint ? paint->Get() : NULL,       //
        backdrop ? backdrop->Get() : NULL  //
    );
    return *this;
  }

  DisplayListBuilder& Scale(float x_scale, float y_scale) {
    gGlobalProcTable.ImpellerDisplayListBuilderScale(Get(),    //
                                                     x_scale,  //
                                                     y_scale);
    return *this;
  }

  DisplayListBuilder& SetTransform(const ImpellerMatrix& transform) {
    gGlobalProcTable.ImpellerDisplayListBuilderSetTransform(Get(), &transform);
    return *this;
  }

  DisplayListBuilder& Transform(const ImpellerMatrix& transform) {
    gGlobalProcTable.ImpellerDisplayListBuilderTransform(Get(), &transform);
    return *this;
  }

  DisplayListBuilder& Translate(float x_translation, float y_translation) {
    gGlobalProcTable.ImpellerDisplayListBuilderTranslate(Get(),          //
                                                         x_translation,  //
                                                         y_translation   //
    );
    return *this;
  }
};

}  // namespace IMPELLER_HPP_NAMESPACE

#endif  // FLUTTER_IMPELLER_TOOLKIT_INTEROP_IMPELLER_HPP_
