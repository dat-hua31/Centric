#pragma once

struct ParticleSystem;

namespace Solver {
  class IForceSolver {
  public:
    virtual ~IForceSolver() = default;
    virtual void solve(ParticleSystem& sys) = 0;
  };
}