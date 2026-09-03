#include "core/application.hpp"
#include "core/logging.hpp"

int main() {
  centric::core::Application application{};  
  application.run();
  return 0;
}