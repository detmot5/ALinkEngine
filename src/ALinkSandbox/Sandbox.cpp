#include <ALinkEngine.h>

#include <iostream>

class SandBox : public ALinkEngine::ALinkApplication {
 public:
  void Init() override {
    ALINK_LOG_WARN("tessst %d", 20);
    ALINK_LOG_ERROR("Testtt %d", 50);
    ALINK_LOG_WARN("iiiiiiiiiiiiii %d", 20);
    ALINK_LOG_INFO("iiiiiiiiiiiiii %d", 400);
  }

  void ShutDown() override {}

  void Run() override {}
};

ALinkEngine::ALinkApplication* ALinkEngine::CreateApplication() {
  return new SandBox();
}
