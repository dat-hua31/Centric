#pragma once

#include "IIntegrator.h"

struct ParticleSystem;
namespace Solver { class IForceSolver; }

namespace Integrator {
  class VerletIntegrator : public IIntegrator {
  public:
    ~VerletIntegrator() override = default;
    void step(ParticleSystem& sys, Solver::IForceSolver& solver, double dt) override;
  };
}