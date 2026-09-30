#pragma once

struct ParticleSystem;
namespace Solver { class IForceSolver; }

namespace Integrator {
  class IIntegrator {
  public:
    virtual ~IIntegrator() = default;
    virtual void step(ParticleSystem& sys, Solver::IForceSolver& solver, double dt) = 0;
  };
}