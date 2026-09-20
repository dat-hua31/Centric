#include "physics/integrators.hpp"

#include "particle/particle_system.hpp"
#include "physics/gravity_solvers.hpp"

#include <cstddef>

namespace centric::physics
{
  void VerletIntegrator::step(
    particle::ParticleSystem& particle_system, 
    GravitySolver& gravity_solver,
    double dt)
  {
    const double half_dt{0.5 * dt};
    const double dt_squared_half{0.5 * dt * dt};
    const std::size_t particle_count{particle_system.getSize()};

    for (std::size_t i = 0; i < particle_count; ++i) {
      particle_system.position_x[i] += particle_system.velocity_x[i] * dt + particle_system.acceleration_x[i] * dt_squared_half;
      particle_system.position_y[i] += particle_system.velocity_y[i] * dt + particle_system.acceleration_y[i] * dt_squared_half;
      particle_system.position_z[i] += particle_system.velocity_z[i] * dt + particle_system.acceleration_z[i] * dt_squared_half;

      particle_system.velocity_x[i] += particle_system.acceleration_x[i] * half_dt;
      particle_system.velocity_y[i] += particle_system.acceleration_y[i] * half_dt;
      particle_system.velocity_z[i] += particle_system.acceleration_z[i] * half_dt;
    }

    gravity_solver.applyAcceleration(particle_system);

    for (std::size_t i = 0; i < particle_count; ++i) {
      particle_system.velocity_x[i] += particle_system.acceleration_x[i] * half_dt;
      particle_system.velocity_y[i] += particle_system.acceleration_y[i] * half_dt;
      particle_system.velocity_z[i] += particle_system.acceleration_z[i] * half_dt;
    }
  }
}