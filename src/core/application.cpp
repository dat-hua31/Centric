#include "core/application.hpp"
#include "core/logging.hpp"

namespace centric::core
{
  [[nodiscard]] bool Application::initialize() noexcept {
    CT_ASSERT(!is_initialized_);
    if (is_initialized_) {
      CT_ERROR("Application::initialize called on an initialized application");
      return false;
    }

    //...

    is_looping_ = true;

    is_initialized_ = true;
    CT_INFO("Application::initialize succeeded");
    return true;
  }
}