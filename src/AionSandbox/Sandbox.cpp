#include <iostream>
#include <AionEngine.h>

class Sandbox : public AionEngine::AionEntryPoint {
 public:

  void run() override {
    std::cout << "Run" << std::endl;
  }
};


AionEngine::AionEntryPoint* AionEngine::CreateEntry() {
  return new Sandbox();
}

