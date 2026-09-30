#include "Integrators/VerletIntegrator.h"

#include "ParticleSystem.h"
#include "IForceSolver.h"

#include <stdexcept>
#include <cstddef>

namespace Integrator {
  void VerletIntegrator::step(ParticleSystem& sys, Solver::IForceSolver& solver, double dt) {
    if (dt <= 0.0) throw std::invalid_argument("Simulation::step: dt must be a positive value");

    const std::size_t n = sys.size();
    const double dt_half = 0.5 * dt;
    const double dt2_half = 0.5 * dt * dt;

    for (std::size_t i = 0; i < n; ++i) {
      sys.x[i]  += sys.vx[i] * dt + sys.ax[i] * dt2_half;
      sys.y[i]  += sys.vy[i] * dt + sys.ay[i] * dt2_half;
      sys.z[i]  += sys.vz[i] * dt + sys.az[i] * dt2_half;

      sys.vx[i] += sys.ax[i] * dt_half;
      sys.vy[i] += sys.ay[i] * dt_half;
      sys.vz[i] += sys.az[i] * dt_half;
    }

    solver.solve(sys);

    for (std::size_t i = 0; i < n; ++i) {
      sys.vx[i] += sys.ax[i] * dt_half;
      sys.vy[i] += sys.ay[i] * dt_half;
      sys.vz[i] += sys.az[i] * dt_half;
    }
  }
}