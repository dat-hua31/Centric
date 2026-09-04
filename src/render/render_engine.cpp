#include "render/render_engine.hpp"

#include "core/logging.hpp"

#include "raylib.h"

namespace centric::render
{
  bool RenderEngine::beginFrame() const noexcept {
    CT_ASSERT(::IsWindowReady());

    if (!::IsWindowReady()) {
      return false;
    }

    ::BeginDrawing();
    ::ClearBackground(WHITE);
    return true;
  }

  void RenderEngine::endFrame() const noexcept {
    CT_ASSERT(::IsWindowReady());

    if (!::IsWindowReady()) {
      return;
    }

    ::EndDrawing();
  }
}