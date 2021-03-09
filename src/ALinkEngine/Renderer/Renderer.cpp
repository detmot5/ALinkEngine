#include "alinkpch.h"
#include "Renderer.h"

namespace ALink {
void Renderer::BeginScene(const OrthographicCamera& camera) {
  sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {

} 

void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<VertexArray>& vertexArray) {
  shader->Bind();
  shader->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace ALink
