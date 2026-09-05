#include "core/application.hpp"

#include "core/logging.hpp"

namespace centric::core
{
  Application::Application() {
    CT_INFO("Application::Application initialization succeeded");
  }

  void Application::run() {
    CT_INFO("Application::run entering loop");
    is_running_ = true;

    while (is_running_ && !window_manager_.shouldClose()) {
      render_engine_.beginFrame();
      
      render_engine_.endFrame();
    }

    CT_INFO("Application::run exiting loop");
  }
}