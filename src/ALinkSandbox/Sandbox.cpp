#include <iostream>
#include <ALinkEngine.h>
#include <unordered_map>

class SandBox : public ALinkEngine::ALinkEntryPoint {
 public:
  SandBox() {
    std::cout << "Init" << std::endl;
  }
  void run() override {
    std::cout << "Run Dupa23456789" << std::endl;
  }
};

ALinkEngine::ALinkEntryPoint* ALinkEngine::createEntry() { return new SandBox(); }
