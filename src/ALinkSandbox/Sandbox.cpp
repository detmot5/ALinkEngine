#include <ALinkEngine.h>

#include <iostream>


class ExampleLayer : public ALinkEngine::Layer {
 public:
  explicit ExampleLayer(const std::string& name)
    : Layer(name) {}

  void OnUpdate() override {
    
  }

  void OnEvent(ALinkEngine::Event& event) {
    ALINK_LOG_WARN("Event from layer: %s", event.ToString().c_str());
  }
};



class SandBox : public ALinkEngine::ALinkApplication {
 public:
  void Init() override {
    ALINK_LOG_WARN("tessst %d", 20);
    ALINK_LOG_ERROR("Testtt %d", 50);
    ALINK_LOG_WARN("iiiiiiiiiiiiii %d", 20);
    ALINK_LOG_INFO("iiiiiiiiiiiiii %d", 400);
    this->AddLayer(new ExampleLayer("Dupa"));
  }

  void ShutDown() override {}

  void Run() override {}
};

ALinkEngine::ALinkApplication* ALinkEngine::CreateApplication() {
  return new SandBox();
}
