#pragma once

#include <fstream>
#include <vector>
#include <string>

class ParticleImporter {

  std::ifstream file_;

public:
  explicit ParticleImporter(const std::string& filename);
  ~ParticleImporter();

  [[nodiscard]] bool loadNextFrame(std::vector<float>& outPositions);
};