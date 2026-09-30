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

#include "raylib.h"

#include <memory>
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <string>
#include <vector>
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
  ::SetTraceLogLevel(LOG_NONE);
  ::InitWindow(kScreenWidth, kScreenHeight, "sim");
  ::SetTargetFPS(kRenderFPS);

  ::Camera3D camera = { 0 };
  camera.position = Vector3{ 15.0f, 15.0f, 15.0f };
  camera.target   = Vector3{ 0.0f, 0.0f, 0.0f };
  camera.up       = Vector3{ 0.0f, 1.0f, 0.0f };
  camera.fovy     = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  ParticleImporter importer("bin/sim.bin");

  Renderer renderer;
  std::vector<float> positions;

  while (!::WindowShouldClose()) {
    ::UpdateCamera(&camera, CAMERA_FREE);

    bool hasData = importer.loadNextFrame(positions);

    ::BeginDrawing();
        ::ClearBackground(BLACK);
        ::BeginMode3D(camera);
          ::DrawGrid(20, 1.0f);
          if (hasData) renderer.draw(positions);
        ::EndMode3D();
        ::DrawFPS(10, 10);
    ::EndDrawing();
  }
  ::CloseWindow();
}

int main() {
  simulateAndExport();
  playback();
  return 0;
}