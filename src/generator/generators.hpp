#pragma once

#include "raylib.h"

#include <cstdint>

namespace centric::particle { class ParticleSystem; }

namespace centric::generator
{
  class Randomizer;

  struct UniformSphereParams {
    double origin_x{};
    double origin_y{};
    double origin_z{};
    double radius{};
    double total_mass{1.0};
    std::size_t particle_count{1};
    ::Color uniform_color{};
  };

  void generateUniformSphere(
    Randomizer& rng, 
    particle::ParticleSystem& particle_system, 
    const UniformSphereParams& params 
  );
}