#include "render/render_engine.hpp"

#include "render/renderers.hpp"
#include "core/logging.hpp"

#include "raylib.h"

#include <memory>

namespace centric::render
{
  RenderEngine::RenderEngine(RendererType renderer_type) noexcept 
    : active_renderer_type_(renderer_type)
  {
    camera_ = {
      .position = {10.0f, 10.0f, 10.0f},
      .target = {0.0f, 0.0f, 0.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .fovy = 70.0f,
      .projection = CAMERA_PERSPECTIVE
    };
    registerRenderers();
    CT_INFO("RenderEngine::RenderEngine intialization succeeded");
  }

  void RenderEngine::beginFrame() noexcept {
    CT_ASSERT(::IsWindowReady());
    ::UpdateCamera(&camera_, CAMERA_FREE);
    ::BeginDrawing();
    ::ClearBackground(BLACK);
    ::DrawFPS(10, 10);
  }

  void RenderEngine::endFrame() const noexcept {
    CT_ASSERT(::IsWindowReady());
    ::EndDrawing();
  }

  void RenderEngine::begin3D() const noexcept {
    CT_ASSERT(::IsWindowReady());
    ::BeginMode3D(camera_);
    ::DrawGrid(10, 10);
  }

  void RenderEngine::end3D() const noexcept {
    CT_ASSERT(::IsWindowReady());
    ::EndMode3D();
  }

  void RenderEngine::registerRenderers() {
    renderers_[RendererType::NaiveRenderer] = std::make_unique<NaiveRenderer>();
  }

  void RenderEngine::setRenderer(RendererType type) {
    CT_ASSERT(renderers_.contains(type));
    active_renderer_type_ = type;
  }

  void RenderEngine::render(const particle::ParticleSystem& particle_system) {
    CT_ASSERT(::IsWindowReady());
    const auto it{renderers_.find(active_renderer_type_)};
    CT_ASSERT(it != renderers_.end() && it->second);
    it->second->draw(particle_system);
  }
}