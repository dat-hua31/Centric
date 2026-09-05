#include "render/render_engine.hpp"

#include "core/logging.hpp"

#include "raylib.h"

namespace centric::render
{
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