#pragma once

namespace centric::particle { class ParticleSystem; }

namespace centric::render
{
  class Renderer {
  public:
    virtual ~Renderer() = default;
    virtual void draw(const particle::ParticleSystem& particle_system) = 0;
  };

  enum class RendererType {
    NaiveRenderer
  };

  class NaiveRenderer : public Renderer {
  public:
    ~NaiveRenderer() override = default;
    void draw(const particle::ParticleSystem& particle_system) override;
  };
}
