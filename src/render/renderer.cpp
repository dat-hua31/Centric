#include "render/renderers.hpp"

#include "particle/particle_system.hpp"

#include "raylib.h"

#include <cstddef>

namespace centric::render
{
  void NaiveRenderer::draw(const particle::ParticleSystem& particle_system) {
    for (std::size_t i = 0; i < particle_system.getSize(); ++i) {
      Vector3 position{
        static_cast<float>(particle_system.position_x[i]),
        static_cast<float>(particle_system.position_y[i]),
        static_cast<float>(particle_system.position_z[i])
      };
      ::DrawSphere(position, particle_system.radius[i], particle_system.color[i]);
    }
  }
}