#include "render/render_engine.hpp"

#include "core/logging.hpp"

#include "raylib.h"

namespace centric::render
{
  RenderEngine::RenderEngine() noexcept {
    camera_ = {
      .position = {10.0f, 10.0f, 10.0f},
      .target = {0.0f, 0.0f, 0.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .fovy = 70.0f,
      .projection = CAMERA_PERSPECTIVE
    };
  }

  void RenderEngine::beginFrame() const noexcept {
    CT_ASSERT(::IsWindowReady());
    ::BeginDrawing();
    ::ClearBackground(WHITE);
  }

  void RenderEngine::endFrame() const noexcept {
    CT_ASSERT(::IsWindowReady());
    ::EndDrawing();
  }
}