#pragma once

#include "physics/gravity_solvers.hpp"
#include "physics/integrators.hpp"

#include <unordered_map>
#include <memory>

namespace centric::particle { class ParticleSystem; }

namespace centric::physics
{
  class PhysicsEngine {
  public:
    explicit PhysicsEngine(
      GravitySolverType solver_type = GravitySolverType::DirectGravitySolver,
      IntegratorType integrator_type = IntegratorType::VerletIntegrator) noexcept;

    ~PhysicsEngine() = default;

    PhysicsEngine(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(const PhysicsEngine&) = delete;
    
    PhysicsEngine(PhysicsEngine&&) = delete;
    PhysicsEngine& operator=(PhysicsEngine&&) = delete;

    void registerGravitySolvers();
    void registerIntegrators();
    void setGravitySolver(GravitySolverType type);
    void setIntegrator(IntegratorType type);
    void step(particle::ParticleSystem& particle_system, double dt);

  private:
    std::unordered_map<GravitySolverType, std::unique_ptr<GravitySolver>> gravity_solvers_{};
    GravitySolverType active_gravity_solver_type_;
    
    std::unordered_map<IntegratorType, std::unique_ptr<Integrator>> integrators_{};
    IntegratorType active_integrator_type_;
  };
}