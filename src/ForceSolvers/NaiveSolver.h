#pragma once

#include "IForceSolver.h"

struct ParticleSystem;

namespace Solver {
  class NaiveSolver : public IForceSolver {

    double eps2_;

  public:
    explicit NaiveSolver(double eps = 0.0) noexcept;
    ~NaiveSolver() override = default;

    void solve(ParticleSystem& sys) override;
  };
}