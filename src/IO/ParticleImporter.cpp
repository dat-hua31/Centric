#include "IO/ParticleImporter.h"

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <ios>

ParticleImporter::ParticleImporter(const std::string& filename) {
  file_.open(filename, std::ios::binary | std::ios::in);
  if (!file_.is_open()) {
    throw std::runtime_error("ParticleImporter: failed to open file: " + filename);
  }
}

ParticleImporter::~ParticleImporter() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool ParticleImporter::loadNextFrame(std::vector<float>& outPositions) {
  if (!file_.is_open()) return false;

  if (file_.peek() == EOF) {
    file_.clear();
    file_.seekg(0, std::ios::beg);
  }

  std::uint32_t count = 0;
  file_.read(reinterpret_cast<char*>(&count), sizeof(count));
  if (file_.gcount() != sizeof(count)) return false;

  outPositions.resize(count * 3);

  const std::streamsize bytesToRead = static_cast<std::streamsize>(outPositions.size() * sizeof(float));
  file_.read(reinterpret_cast<char*>(outPositions.data()), bytesToRead);

  return file_.gcount() == bytesToRead;
}