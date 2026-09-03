#pragma once

namespace centric::core
{
  class WindowManager {
  public:
    WindowManager();
    ~WindowManager();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;
    WindowManager& operator=(WindowManager&&) = delete;

    [[nodiscard]] bool shouldClose() const noexcept;
  private:
    int target_fps_{60};
  };
}