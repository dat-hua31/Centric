#include "physics/physics_engine.hpp"

#include "physics/gravity_solvers.hpp"
#include "physics/integrators.hpp"
#include "core/logging.hpp"

#include <unordered_map>
#include <memory>

namespace centric::physics
{
  PhysicsEngine::PhysicsEngine(GravitySolverType solver_type, IntegratorType integrator_type) noexcept 
    : active_gravity_solver_type_(solver_type), 
      active_integrator_type_(integrator_type) {
      registerGravitySolvers();
      registerIntegrators();
      CT_INFO("PhysicsEngine::PhysicsEngine initialization succeeded");
    }

  void PhysicsEngine::registerGravitySolvers() {
    gravity_solvers_[GravitySolverType::DirectGravitySolver] = std::make_unique<DirectGravitySolver>();
  }

  void PhysicsEngine::registerIntegrators() {
    integrators_[IntegratorType::VerletIntegrator] = std::make_unique<VerletIntegrator>();
  }

  void PhysicsEngine::setGravitySolver(GravitySolverType type) {
    CT_ASSERT(gravity_solvers_.contains(type));
    active_gravity_solver_type_ = type;
  }

  void PhysicsEngine::setIntegrator(IntegratorType type) {
    CT_ASSERT(integrators_.contains(type));
    active_integrator_type_ = type;
  }

  void PhysicsEngine::step(particle::ParticleSystem& particle_system, double dt) {
    const auto solver_it{gravity_solvers_.find(active_gravity_solver_type_)};
    const auto integrator_it{integrators_.find(active_integrator_type_)};
    CT_ASSERT(solver_it != gravity_solvers_.end());
    CT_ASSERT(integrator_it != integrators_.end());
    integrator_it->second->step(particle_system, *(solver_it->second), dt);
  }
}