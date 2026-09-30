#include "IO/ParticleExporter.h"

#include "ParticleSystem.h"

#include <fstream>
#include <cstddef>
#include <cstdint>
#include <string>
#include <stdexcept>

ParticleExporter::ParticleExporter(const std::string& filename, std::size_t frameInterval)
  : frameInterval_(frameInterval), currentStep_(0)
{
  file_.open(filename, std::ios::binary | std::ios::out);
  if (!file_.is_open()) {
    throw std::runtime_error("ParticleExporter: failed to open file: " + filename);
  }
}

ParticleExporter::~ParticleExporter() {
  if (file_.is_open()) file_.close();
}

void ParticleExporter::capture(const ParticleSystem& sys) {
  if (!file_.is_open()) return;
  if (currentStep_++ % frameInterval_ != 0) return;

  const std::size_t particleCount = sys.size();
  const std::uint32_t count = static_cast<std::uint32_t>(particleCount);
  file_.write(reinterpret_cast<const char*>(&count), sizeof(count));

  buffer_.resize(particleCount * 3);

  for (std::size_t i = 0; i < particleCount; ++i) {
    buffer_[i * 3]     = static_cast<float>(sys.x[i]);
    buffer_[i * 3 + 1] = static_cast<float>(sys.y[i]);
    buffer_[i * 3 + 2] = static_cast<float>(sys.z[i]);
  }

  file_.write(reinterpret_cast<const char*>(buffer_.data()), buffer_.size() * sizeof(float));
}