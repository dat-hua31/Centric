#pragma once

namespace centric::render
{
  class RenderEngine {
  public:
    RenderEngine() noexcept = default;
    ~RenderEngine() = default;

    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;
    
    RenderEngine(RenderEngine&&) = delete;
    RenderEngine& operator=(RenderEngine&&) = delete;

    void beginFrame() const noexcept;
    void endFrame() const noexcept;

  private:
  };
}