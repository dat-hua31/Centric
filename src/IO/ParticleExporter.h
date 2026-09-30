#pragma once

#include <fstream>
#include <cstddef>
#include <string>
#include <vector>

struct ParticleSystem;

class ParticleExporter {

  std::ofstream file_;
  std::size_t frameInterval_;
  std::size_t currentStep_;
  std::vector<float> buffer_;

public:
  explicit ParticleExporter(const std::string& filename, std::size_t frameInterval = 1);
  ~ParticleExporter();

  ParticleExporter(const ParticleExporter&) = delete;
  ParticleExporter& operator=(const ParticleExporter&) = delete;

  void capture(const ParticleSystem& sys);
};