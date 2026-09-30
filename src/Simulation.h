#pragma once

#include "IForceSolver.h"
#include "IIntegrator.h"
#include "IO/ParticleExporter.h"

#include <memory>

struct ParticleSystem;

class Simulation {

  std::unique_ptr<Solver::IForceSolver> solver_;
  std::unique_ptr<Integrator::IIntegrator> integrator_;
  std::unique_ptr<ParticleExporter> exporter_;

public:
  explicit Simulation(
    std::unique_ptr<Solver::IForceSolver> solver,
    std::unique_ptr<Integrator::IIntegrator> integrator,
    std::unique_ptr<ParticleExporter> exporter = nullptr
  ) noexcept;

  void setSolver(std::unique_ptr<Solver::IForceSolver> solver) noexcept;
  void setIntegrator(std::unique_ptr<Integrator::IIntegrator> integrator) noexcept;
  void setExporter(std::unique_ptr<ParticleExporter> exporter) noexcept;

  void step(ParticleSystem& sys, double dt);
};