#pragma once

#include "core/window_manager.hpp"

namespace centric::core
{
  class Application {
  public:
    Application();
    ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    void run();

  private:
    bool is_running_{false};

    WindowManager window_manager_{};
  };
}