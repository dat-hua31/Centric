#include "Generators/Generators.h"

#include <cstddef>
#include <cstdint>
#include <random>
#include <stdexcept>

#include "ParticleSystem.h"

namespace Generator {
  void generateSphere(ParticleSystem& sys, std::size_t count,
                      double radius, double totalMass,
                      double originX, double originY, double originZ,
                      std::uint32_t seed) 
  {
    if (radius < 0.0) { 
      throw std::invalid_argument("generateSphere: 'radius' must be a non-negative value");
    }

    if (totalMass <= 0.0) {
      throw std::invalid_argument("generateSphere: 'totalMass' must be a positive value");
    }

    if (count == 0) return;

    sys.resize(count);

    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    double perParticleMass = totalMass / static_cast<double>(count);

    for (std::size_t i = 0; i < count; ++i) {
      double x, y, z;
      do {
        x = dist(rng);
        y = dist(rng);
        z = dist(rng);
      } while (x * x + y * y + z * z > 1.0);
      sys.x[i] = x * radius + originX;
      sys.y[i] = y * radius + originY;
      sys.z[i] = z * radius + originZ;
      sys.mass[i] = perParticleMass;
    }
    sys.resetVelocity();
    sys.resetAcceleration();
  }
}