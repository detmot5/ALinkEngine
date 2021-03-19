#include "alinkpch.h"
#include "Renderer2D.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace ALink {

struct Renderer2DStorage {
  std::shared_ptr<VertexArray> quarVertexArray;
  std::shared_ptr<Shader> flatColorShader;
  glm::mat4 viewProjectionMatrix;
};

static Renderer2DStorage* rendererStorage = nullptr;

void Renderer2D::Init() {
  rendererStorage = new Renderer2DStorage();
  rendererStorage->quarVertexArray = VertexArray::Create();


  float sqverticies[4 * 5] = {
    -0.9f, -0.75f, 1.0f,  0.0f, 0.0f,
    0.9f, -0.75f, 1.0f,  1.0f, 0.0f,
    0.9f,  0.75f, 1.0f,  1.0f, 1.0f,
    -0.9f,  0.75f, 1.0f,  0.0f, 1.0f
  };


  std::shared_ptr<ALink::VertexBuffer> squareVB = ALink::VertexBuffer::Create(sqverticies, sizeof(sqverticies));
  squareVB->SetLayout({
    {ALink::ShaderDataType::Float3, "a_Position"},
    {ALink::ShaderDataType::Float2, "a_TextureCoords"},
  });
  rendererStorage->quarVertexArray->AddVertexBuffer(squareVB);
  uint32_t sqindicies[] = {
    0, 1, 2,
    2, 3, 0
  };

  rendererStorage->flatColorShader = Shader::Create("../../../../assets/shaders/main.glsl");



}

void Renderer2D::ShutDown() {
  delete rendererStorage;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
  rendererStorage->viewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer2D::EndScene() {

}

void Renderer2D::DrawQuad(const glm::vec2& positions, const glm::vec2& size,
                          const glm::vec4& color) {

}

void Renderer2D::DrawQuad(const glm::vec3& positions, const glm::vec2& size,
                          const glm::vec4& color) {
  
}
}   // namespace ALink