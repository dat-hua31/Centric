#pragma once

#include "core/logging.hpp"

#include <random>
#include <cstdint>
#include <concepts>

namespace centric::generator
{
  class Randomizer {
  public:
    explicit Randomizer(std::uint64_t seed);

    void setSeed(std::uint64_t seed);
    
    template <std::floating_point T>
    [[nodiscard]] T getReal(T min, T max) {
      CT_ASSERT(min <= max);
      std::uniform_real_distribution<T> dist(min, max);
      return dist(rng_);
    }

  private: 
    std::mt19937_64 rng_;
  };
}