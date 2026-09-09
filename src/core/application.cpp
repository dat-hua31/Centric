#include "core/application.hpp"

#include "core/window_manager.hpp"
#include "render/render_engine.hpp"
#include "generator/generators.hpp"
#include "generator/randomizer.hpp"
#include "particle/particle_system.hpp"
#include "core/logging.hpp"

namespace centric::core
{
  Application::Application() {
    CT_INFO("Application::Application initialization succeeded");
  }

  void Application::run() {
    CT_INFO("Application::run entering loop");
    is_running_ = true;

    generator::Randomizer rng{42};
    particle::ParticleSystem particle_system{};
    generator::UniformSphereParams params{
      .radius = 10.0,
      .particle_count = 100
    };
    generator::generateUniformSphere(rng, particle_system, params);

    while (is_running_ && !window_manager_.shouldClose()) {
      render_engine_.beginFrame();
      //...
      render_engine_.endFrame();
    }

    CT_INFO("Application::run exiting loop");
  }
}