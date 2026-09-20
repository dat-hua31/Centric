#include "core/application.hpp"

#include "core/window_manager.hpp"
#include "render/render_engine.hpp"
#include "generator/generators.hpp"
#include "generator/randomizer.hpp"
#include "particle/particle_system.hpp"
#include "physics/physics_engine.hpp"
#include "core/logging.hpp"

namespace centric::core
{
  Application::Application() {
    CT_INFO("Application::Application initialization succeeded");
  }

  void Application::run() {
    CT_INFO("Application::run entering loop");
    is_running_ = true;

    generator::Randomizer rng{};
    particle::ParticleSystem particle_system{};
    generator::UniformSphereParams params{
      .radius = 10.0,
      .total_mass = 100.0,
      .particle_count = 100,
      .particle_radius = 0.1,
      .uniform_color = YELLOW,
    };
    generator::generateUniformSphere(rng, particle_system, params);

    constexpr double physics_dt{1.0 / 60.0};
    double accumulator{0.0};

    double previous_time{window_manager_.getTime()};

    while (is_running_ && !window_manager_.shouldClose()) {
      double current_time{window_manager_.getTime()};
      double frame_time{current_time - previous_time};
      previous_time = current_time;

      if (frame_time > 0.25) {
        frame_time = 0.25;
      }

      accumulator += frame_time;

      while (accumulator >= physics_dt) {
        physics_engine_.step(particle_system, physics_dt);
        accumulator -= physics_dt;
      }

      render_engine_.beginFrame();
      
      render_engine_.begin3D();
      render_engine_.render(particle_system);
      render_engine_.end3D();

      render_engine_.endFrame();
    }

    CT_INFO("Application::run exiting loop");
  }
}