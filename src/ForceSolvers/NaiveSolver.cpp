#include "ForceSolvers/NaiveSolver.h"

#include "ParticleSystem.h"

#include <cmath>
#include <cstddef>

namespace Solver {
  NaiveSolver::NaiveSolver(double eps) noexcept : eps2_(eps * eps) {}
    
  void NaiveSolver::solve(ParticleSystem& sys) {
    const std::size_t n = sys.size();
    sys.resetAcceleration();

    const double* __restrict x = sys.x.data();
    const double* __restrict y = sys.y.data();
    const double* __restrict z = sys.z.data();
    const double* __restrict m = sys.mass.data();

    double* __restrict ax = sys.ax.data();
    double* __restrict ay = sys.ay.data();
    double* __restrict az = sys.az.data();

    for (std::size_t i = 0; i < n; ++i) {
      const double xi = x[i];
      const double yi = y[i];
      const double zi = z[i];
      double axi = 0.0;
      double ayi = 0.0;
      double azi = 0.0;
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) continue;
        const double dx = x[j] - xi;
        const double dy = y[j] - yi;
        const double dz = z[j] - zi;
        const double r2 = dx * dx + dy * dy + dz * dz + eps2_;
        const double inv_r = 1.0 / std::sqrt(r2);
        const double inv_r3 = inv_r * inv_r * inv_r;
        const double f = m[j] * inv_r3;
        axi += f * dx;
        ayi += f * dy;
        azi += f * dz;
      }
      ax[i] = axi;
      ay[i] = ayi;
      az[i] = azi;
    }
  }
}