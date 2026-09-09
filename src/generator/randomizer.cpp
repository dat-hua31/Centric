#include "generator/randomizer.hpp"

#include <random>
#include <cstdint>

namespace centric::generator
{
  Randomizer::Randomizer(std::uint64_t seed) : rng_(seed) {}

  void Randomizer::setSeed(std::uint64_t seed) {
    rng_.seed(seed);
  }
}