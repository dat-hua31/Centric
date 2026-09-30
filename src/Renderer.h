#pragma once

#include "raylib.h"

#include <vector>

class ParticleImporter;

class Renderer {

  ::Camera3D camera_;
  ::Mesh mesh_;
  ::Material material_;
  std::vector<::Matrix> transforms_;

public:
  explicit Renderer(int screenWidth = 1280, int screenHeight = 720);
  ~Renderer();

  void render(ParticleImporter& importer, double fps);

  void draw(const std::vector<float>& positions);
};