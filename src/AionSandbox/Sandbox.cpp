#include <iostream>
#include <AionEngine.h>


class Sandbox : public AionEngine::AionEntryPoint {
 public:
  Sandbox() {
     
  }
  void run() override {
    std::cout << "Run Dupa23" << std::endl;
  }
};


AionEngine::AionEntryPoint* AionEngine::CreateEntry() {
  return new Sandbox();
}

