#include "core/application.hpp"

#include "core/logging.hpp"

#include "raylib.h" // demonstration purpose

namespace centric::core
{
  Application::Application() {
    CT_INFO("Application::Application initialization succeeded");
  }

  void Application::run() {
    CT_INFO("Application::run entering loop");
    is_running_ = true;

    while (is_running_ && !window_manager_.shouldClose()) {
      ::BeginDrawing(); // demonstration purpose
      ::ClearBackground(WHITE); // demonstration purpose

      ::EndDrawing(); // demonstration purpose
    }

    CT_INFO("Application::run exiting loop");
  }
}