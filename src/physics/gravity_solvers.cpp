#include "physics/gravity_solvers.hpp"

#include "particle/particle_system.hpp"

#include <cstddef>
#include <cmath>

namespace centric::physics
{
  DirectGravitySolver::DirectGravitySolver(double epsilon) noexcept 
    : epsilon_squared_(epsilon * epsilon) {}

  void DirectGravitySolver::applyAcceleration(particle::ParticleSystem& particle_system) {
    const std::size_t particle_count{particle_system.getSize()};

    for (std::size_t i = 0; i < particle_count; ++i) {
      particle_system.acceleration_x[i] = 0.0;
      particle_system.acceleration_y[i] = 0.0;
      particle_system.acceleration_z[i] = 0.0;
    }

    // i: attractor, j: being acted upon
    for (std::size_t i = 0; i < particle_count; ++i) {
      for (std::size_t j = 0; j < particle_count; ++j) {
        if (i == j) { continue; }

        const double dx{particle_system.position_x[i] - particle_system.position_x[j]};
        const double dy{particle_system.position_y[i] - particle_system.position_y[j]};
        const double dz{particle_system.position_z[i] - particle_system.position_z[j]};
        const double distance_squared{dx * dx + dy * dy + dz * dz + epsilon_squared_};

        const double inverse_distance{1.0 / std::sqrt(distance_squared)};
        const double inverse_distance_cubed{inverse_distance * inverse_distance * inverse_distance};
        const double acceleration_scalar{particle_system.mass[i] * inverse_distance_cubed};

        particle_system.acceleration_x[j] += acceleration_scalar * dx;
        particle_system.acceleration_y[j] += acceleration_scalar * dy;
        particle_system.acceleration_z[j] += acceleration_scalar * dz;
      }
    }
  }

  void DirectGravitySolver::setEpsilon(double epsilon) noexcept {
    epsilon_squared_ = epsilon * epsilon;
  }
}