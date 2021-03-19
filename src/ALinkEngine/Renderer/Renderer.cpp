#include "alinkpch.h"
#include "Renderer.h"
#include "GraphicsAPI/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ALink {
void Renderer::Init() {
  RenderCommand::Init();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
  RenderCommand::SetViewPort(width, height);
}
void Renderer::BeginScene(const OrthographicCamera& camera) {
  sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {

} 

void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                        const std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4& transform) {
  shader->Bind();
  std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
  std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace ALink
  