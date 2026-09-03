#pragma once

namespace centric::core
{
  class Application {
  public:
    Application() noexcept = default;
    ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    [[nodiscard]] bool initialize() noexcept;
  private:
    bool is_initialized_{false};
    bool is_looping_{false};
  };
}