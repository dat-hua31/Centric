#pragma once

#include "render/renderers.hpp"

#include "raylib.h"

#include <memory>
#include <unordered_map>

namespace centric::particle { class ParticleSystem; }

namespace centric::render
{
  class RenderEngine {
  public:
    explicit RenderEngine(RendererType renderer_type = RendererType::NaiveRenderer) noexcept;
    ~RenderEngine() = default;

    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;
    
    RenderEngine(RenderEngine&&) = delete;
    RenderEngine& operator=(RenderEngine&&) = delete;

    void beginFrame() noexcept;
    void endFrame() const noexcept;
    void begin3D() const noexcept;
    void end3D() const noexcept;

    void registerRenderers();
    void setRenderer(RendererType type);
    void render(const particle::ParticleSystem& particle_system);

  private:
    ::Camera3D camera_{};
    std::unordered_map<RendererType, std::unique_ptr<Renderer>> renderers_{};
    RendererType active_renderer_type_;
  };
}