#pragma once

#include "raylib.h"

#include <vector>

class Renderer {

  ::Mesh mesh_;
  ::Material material_;
  std::vector<::Matrix> transforms_;

public:
  Renderer();
  ~Renderer();

  void draw(const std::vector<float>& positions);
};