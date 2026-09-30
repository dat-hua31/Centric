#include "Renderer.h"

#include "IO/ParticleImporter.h"

#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <cstddef>
#include <stdexcept>
#include <print>

Renderer::Renderer(int screenWidth, int screenHeight) {
  ::SetTraceLogLevel(LOG_NONE);
  ::InitWindow(screenWidth, screenHeight, "sim");

  camera_.position = Vector3{ 15.0f, 15.0f, 15.0f };
  camera_.target   = Vector3{ 0.0f, 0.0f, 0.0f };
  camera_.up       = Vector3{ 0.0f, 1.0f, 0.0f };
  camera_.fovy     = 45.0f;
  camera_.projection = CAMERA_PERSPECTIVE;

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

void Renderer::render(ParticleImporter& importer, double fps)
{
  if (fps < 0.0) throw std::invalid_argument("FPS can only be a positive value");
  ::SetTargetFPS(fps);

  std::vector<float> positions;
  while (!::WindowShouldClose()) {
    ::UpdateCamera(&camera_, CAMERA_FREE);
    
    bool hasData = importer.loadNextFrame(positions);
    if (!hasData) std::println("WARNING: Renderer::render tried to load a corrupted frame");

    ::BeginDrawing();
        ::ClearBackground(BLACK);

        ::BeginMode3D(camera_);
          ::DrawGrid(20, 1.0f);
          if (hasData) draw(positions);
        ::EndMode3D();

        ::DrawFPS(10, 10);
    ::EndDrawing();
  }
  ::CloseWindow();
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