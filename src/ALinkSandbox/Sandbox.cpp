#include <ALinkEngine.h>

#include <iostream>


class ExampleLayer : public ALinkEngine::Layer {
 public:
  explicit ExampleLayer(const std::string& name)
    : Layer(name) {}

  void OnUpdate() override {
    
  }

  void OnEvent(ALinkEngine::Event& event) override {
    
  }

  void OnImGuiRender() override {
    ImGui::Begin("Doopa");
    
    if (ImGui::Button("click")) {
      ALINK_LOG_INFO("Ouch");
    }
    ImGui::End();
  }

};



class SandBox : public ALinkEngine::ALinkApplication {
 public:
  void Init() override {
    this->AddLayer(new ExampleLayer("Dupa"));
  }

  void ShutDown() override {}

  void Run() override {}
};

ALinkEngine::ALinkApplication* ALinkEngine::CreateApplication() {
  return new SandBox();
}
