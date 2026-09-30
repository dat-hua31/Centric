#include "Renderer.h"

#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <cstddef>

Renderer::Renderer() {
  mesh_ = ::GenMeshSphere(0.1f, 4, 4);
  material_ = ::LoadMaterialDefault();

  ::Shader shader = ::LoadShader("../shaders/instancing.vs", "../shaders/instancing.fs");
  shader.locs[SHADER_LOC_MATRIX_MVP] = ::GetShaderLocation(shader, "mvp");
  shader.locs[SHADER_LOC_MATRIX_MODEL] = ::GetShaderLocationAttrib(shader, "instanceTransform");

  material_.shader = shader;
}

Renderer::~Renderer() {
  ::UnloadMaterial(material_);
  ::UnloadMesh(mesh_);
}

void Renderer::draw(const std::vector<float>& positions) {
  const std::size_t count = positions.size() / 3;
  if (count == 0) return;
  transforms_.resize(count);
  for (std::size_t i = 0; i < count; ++i) {
    const std::size_t idx = i * 3;
    transforms_[i] = ::MatrixTranslate(positions[idx], 
                                       positions[idx + 1], 
                                       positions[idx + 2]);
  }
  ::DrawMeshInstanced(mesh_, material_, transforms_.data(), static_cast<int>(count));
}