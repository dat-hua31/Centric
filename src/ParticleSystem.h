#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>

struct ParticleSystem {
  std::vector<double> x, y, z;
  std::vector<double> vx, vy, vz;
  std::vector<double> ax, ay, az;
  std::vector<double> mass;

  [[nodiscard]] std::size_t size() const noexcept { 
    return x.size(); 
  }

  void resize(std::size_t count) {
    x.resize(count); y.resize(count); z.resize(count); 
    vx.resize(count); vy.resize(count); vz.resize(count); 
    ax.resize(count); ay.resize(count); az.resize(count); 
    mass.resize(count);
  }

  void resetVelocity() {
    std::fill(vx.begin(), vx.end(), 0.0);
    std::fill(vy.begin(), vy.end(), 0.0);
    std::fill(vz.begin(), vz.end(), 0.0);
  }

  void resetAcceleration() {
    std::fill(ax.begin(), ax.end(), 0.0);
    std::fill(ay.begin(), ay.end(), 0.0);
    std::fill(az.begin(), az.end(), 0.0);
  }

  ParticleSystem& operator+=(const ParticleSystem& other) {
    x.insert(x.end(), other.x.begin(), other.x.end());
    y.insert(y.end(), other.y.begin(), other.y.end());
    z.insert(z.end(), other.z.begin(), other.z.end());

    vx.insert(vx.end(), other.vx.begin(), other.vx.end());
    vy.insert(vy.end(), other.vy.begin(), other.vy.end());
    vz.insert(vz.end(), other.vz.begin(), other.vz.end());

    ax.insert(ax.end(), other.ax.begin(), other.ax.end());
    ay.insert(ay.end(), other.ay.begin(), other.ay.end());
    az.insert(az.end(), other.az.begin(), other.az.end());

    mass.insert(mass.end(), other.mass.begin(), other.mass.end());

    return *this;
  }

  [[nodiscard]] ParticleSystem operator+(const ParticleSystem& rhs) const {
    ParticleSystem result = *this;
    result += rhs;
    return result;
  }
};