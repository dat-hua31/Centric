#include "core/application.hpp"
#include "core/logging.hpp"

int main() {
  centric::core::Application application{};  
  
  if (!application.initialize()) {
    CT_FATAL("main failed to initialize application");
  }

  return 0;
}