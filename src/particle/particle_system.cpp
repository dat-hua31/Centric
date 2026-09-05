#include "particle/particle_system.hpp"

#include <vector>
#include <cstddef>

namespace centric::particle
{
  void ParticleSystem::reserve(std::size_t capacity) {
    mass.reserve(capacity);
    position_x.reserve(capacity);
    position_y.reserve(capacity);
    position_z.reserve(capacity);
    velocity_x.reserve(capacity);
    velocity_y.reserve(capacity);
    velocity_z.reserve(capacity);
    color.reserve(capacity);
  }

  void ParticleSystem::resize(std::size_t new_size) {
    mass.resize(new_size);
    position_x.resize(new_size);
    position_y.resize(new_size);
    position_z.resize(new_size);
    velocity_x.resize(new_size);
    velocity_y.resize(new_size);
    velocity_z.resize(new_size);
    color.resize(new_size);
  }

  void ParticleSystem::clear() noexcept {
    mass.clear();
    position_x.clear();
    position_y.clear();
    position_z.clear();
    velocity_x.clear();
    velocity_y.clear();
    velocity_z.clear();
    color.clear();
  }

  std::size_t ParticleSystem::size() const noexcept {
    return mass.size();
  }

  bool ParticleSystem::isEmpty() const noexcept {
    return mass.empty();
  }
}