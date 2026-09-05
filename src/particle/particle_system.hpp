#pragma once

#include "raylib.h"

#include <vector>
#include <cstddef>

namespace centric::particle
{
  struct ParticleSystem {
    std::vector<double> mass{};

    std::vector<double> position_x{};
    std::vector<double> position_y{};
    std::vector<double> position_z{};

    std::vector<double> velocity_x{};
    std::vector<double> velocity_y{};
    std::vector<double> velocity_z{};

    std::vector<::Color> color{};

    void reserve(std::size_t capacity);
    void resize(std::size_t new_size);
    void clear() noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool isEmpty() const noexcept;
  };
}