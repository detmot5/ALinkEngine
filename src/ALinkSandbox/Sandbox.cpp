#include <ALinkEngine.h>

#include <iostream>

class ExampleLayer : public ALinkEngine::Layer {
 public:
  explicit ExampleLayer(const std::string& name) : Layer(name) {}

  void OnUpdate() override {
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    RenderCommand::Clear();
    Renderer::BeginScene(this->camera);
    Renderer::Submit(this->shader, this->squareVA);
    Renderer::Submit(this->shader, this->vertexArray);
    Renderer::EndScene();
  }

  void OnEvent(ALinkEngine::Event& event) override {}

  void OnImGuiRender() override {
    ImGui::Begin("Doopa");
    if (ImGui::Button("click")) {
      ALINK_LOG_INFO("Ouch");
    }
    ImGui::End();
  }

 private:
  std::shared_ptr<Shader> shader;
  std::shared_ptr<VertexArray> vertexArray;

  std::shared_ptr<VertexArray> squareVA;
  OrthographicCamera camera;
};

class SandBox : public ALinkEngine::ALinkApplication {
 public:
  void Init() override { this->AddLayer(new ExampleLayer("Dupa")); }

  void ShutDown() override {}

  void Run() override {}
};

ALinkEngine::ALinkApplication* ALinkEngine::CreateApplication() {
  return new SandBox();
}
