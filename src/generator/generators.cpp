#include "generator/generators.hpp"

#include "particle/particle_system.hpp"
#include "core/logging.hpp"
#include "generator/randomizer.hpp"

#include <cstdint>

namespace centric::generator
{
  void generateUniformSphere(
    Randomizer& rng, 
    particle::ParticleSystem& particle_system, 
    const UniformSphereParams& params 
  ) {
    CT_ASSERT(params.radius >= 0.0);
    CT_ASSERT(params.total_mass >= 0.0);

    if (params.particle_count == 0) {
      CT_WARN("generateUniformSphere called with a 0 particle count parameter set");
      return;
    }

    const std::size_t start_idx{particle_system.getSize()};
    particle_system.resize(start_idx + params.particle_count);

    const double mass_per_particle{params.total_mass / static_cast<double>(params.particle_count)};

    for (std::size_t i = 0; i < params.particle_count; ++i) {
      double ux, uy, uz, udist_squared;
      do {
        ux = rng.getReal(-1.0, 1.0);
        uy = rng.getReal(-1.0, 1.0);
        uz = rng.getReal(-1.0, 1.0);
        udist_squared = ux * ux + uy * uy + uz * uz;
      } while (udist_squared > 1.0);

      std::size_t idx{start_idx + i};
      particle_system.position_x[idx] = params.origin_x + ux * params.radius; 
      particle_system.position_y[idx] = params.origin_y + uy * params.radius;
      particle_system.position_z[idx] = params.origin_z + uz * params.radius;
      particle_system.mass[idx] = mass_per_particle;
      particle_system.color[idx] = params.uniform_color;
    }
  }
}