#include "ParticleSystem.h"
#include "Generators/Generators.h"
#include "IForceSolver.h"
#include "ForceSolvers/NaiveSolver.h"
#include "IIntegrator.h"
#include "Integrators/VerletIntegrator.h"
#include "IO/ParticleExporter.h"
#include "IO/ParticleImporter.h"
#include "Renderer.h" 
#include "Simulation.h"

#include <memory>
#include <cstddef>
#include <print>

namespace
{
  constexpr double kTotalSimTime = 10.0;
  constexpr double kPhysicsDT = 0.001;
  constexpr double kRenderFPS = 60.0;
  constexpr std::size_t kPhysicsSteps = static_cast<std::size_t>(kTotalSimTime / kPhysicsDT);
  constexpr std::size_t kRenderFrames = static_cast<std::size_t>(kTotalSimTime * kRenderFPS);
  constexpr std::size_t kFrameInterval = static_cast<std::size_t>(kPhysicsSteps / kRenderFrames);
  constexpr double kEps = 0.5;
  constexpr int kScreenWidth = 1280;
  constexpr int kScreenHeight = 720;
}

void simulateAndExport() {
  ParticleSystem sys;
  Generator::generateSphere(sys, 100);

  std::println("Total Particle Count: {}", sys.size());
  std::println("Total Simulation Time: {} seconds", kTotalSimTime);
  std::println("Physics DT: {} seconds", kPhysicsDT);
  std::println("Render FPS: {}", kRenderFPS);
  std::println("Physics Steps: {}", kPhysicsSteps);
  std::println("Render Frames: {}", kRenderFrames);
  std::println("Frame Interval: {}", kFrameInterval);
  std::println("Epsilon Softening: {}", kEps);

  Simulation sim(
    std::make_unique<Solver::NaiveSolver>(kEps),
    std::make_unique<Integrator::VerletIntegrator>(),
    std::make_unique<ParticleExporter>("bin/sim.bin", kFrameInterval)
  );
  
  for (std::size_t i = 0; i < kPhysicsSteps; ++i) {
    sim.step(sys, kPhysicsDT);
  }
}

void playback() {  
  ParticleImporter importer("bin/sim.bin");
  Renderer renderer;
  renderer.render(importer, kRenderFPS);  
}

int main() {
  simulateAndExport();
  playback();
  return 0;
}