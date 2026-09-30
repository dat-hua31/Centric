#include "Simulation.h"

#include "ParticleSystem.h"
#include "IForceSolver.h"
#include "IIntegrator.h"
#include "IO/ParticleExporter.h"

#include <memory>
#include <utility>
#include <stdexcept>

Simulation::Simulation(
  std::unique_ptr<Solver::IForceSolver> solver,
  std::unique_ptr<Integrator::IIntegrator> integrator,
  std::unique_ptr<ParticleExporter> exporter
) noexcept 
  : solver_(std::move(solver)), 
    integrator_(std::move(integrator)),
    exporter_(std::move(exporter))
  {}

void Simulation::setSolver(std::unique_ptr<Solver::IForceSolver> solver) noexcept {
  solver_ = std::move(solver);
}

void Simulation::setIntegrator(std::unique_ptr<Integrator::IIntegrator> integrator) noexcept {
  integrator_ = std::move(integrator);
}

void Simulation::setExporter(std::unique_ptr<ParticleExporter> exporter) noexcept {
  exporter_ = std::move(exporter);
}

void Simulation::step(ParticleSystem& sys, double dt) {
  if (dt <= 0.0) {
    throw std::invalid_argument("Simulation::step: dt must be a positive value");
  }
  if (!solver_ || !integrator_) return;

  if (exporter_) exporter_->capture(sys);
  integrator_->step(sys, *solver_, dt);
}