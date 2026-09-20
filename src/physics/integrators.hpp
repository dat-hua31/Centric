#pragma once

namespace centric::particle { class ParticleSystem; }

namespace centric::physics
{
  class GravitySolver;

  class Integrator {
  public:
    virtual ~Integrator() = default;
    virtual void step(
      particle::ParticleSystem& particle_system, 
      GravitySolver& gravity_solver,
      double dt) = 0;
  };

  enum class IntegratorType {
    VerletIntegrator
  };

  class VerletIntegrator : public Integrator {
  public:
    ~VerletIntegrator() override = default;

    void step(
      particle::ParticleSystem& particle_system, 
      GravitySolver& gravity_solver,
      double dt) override;
  };
}