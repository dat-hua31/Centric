#pragma once

#include <cstddef>
#include <cstdint>

struct ParticleSystem;

namespace Generator {
  void generateSphere(ParticleSystem& sys, std::size_t count = 100,
                      double radius = 10.0, double totalMass = 100.0,
                      double originX = 0.0, double originY = 0.0, double originZ = 0.0,
                      std::uint32_t seed = 42);
}