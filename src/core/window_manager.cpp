#include "core/window_manager.hpp"

#include "core/logging.hpp"

#include "raylib.h"

namespace centric::core
{
  WindowManager::WindowManager() {
    ::SetTraceLogLevel(LOG_NONE);
    ::InitWindow(1280, 720, "centric");
    if (!::IsWindowReady()) {
      CT_FATAL("WindowManager::WindowManager failed to create window context");
    }

    int current_monitor{::GetCurrentMonitor()};
    int monitor_width{::GetMonitorWidth(current_monitor)};
    int monitor_height{::GetMonitorHeight(current_monitor)};
    ::SetWindowSize(monitor_width * 0.9, monitor_height * 0.9);
    ::SetWindowPosition(monitor_width * 0.05, monitor_height * 0.05);
    ::SetTargetFPS(target_fps_);

    CT_INFO("WindowManager::WindowManager initialization succeeded");
  }

  WindowManager::~WindowManager() {
    if (::IsWindowReady()) {
      ::CloseWindow();
    }
  }

  bool WindowManager::shouldClose() const noexcept {
    if (!::IsWindowReady()) {
      return true;
    }
    return ::WindowShouldClose();
  }
}