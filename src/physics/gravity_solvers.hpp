#pragma once

namespace centric::particle { class ParticleSystem; }

namespace centric::physics
{
  class GravitySolver {
  public:
    virtual ~GravitySolver() = default;
    virtual void applyAcceleration(particle::ParticleSystem& particle_system) = 0;
  };

  enum class GravitySolverType {
    DirectGravitySolver
  };

  class DirectGravitySolver : public GravitySolver {
  public:
    explicit DirectGravitySolver(double epsilon = 0.5) noexcept;

    ~DirectGravitySolver() override = default;

    void applyAcceleration(particle::ParticleSystem& particle_system) override;
    void setEpsilon(double epsilon) noexcept; 

  private:
    double epsilon_squared_;
  };
}