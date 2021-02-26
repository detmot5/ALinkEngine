#include "Application.h"

namespace ALinkEngine {
ALinkApplication::ALinkApplication() {}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
  loguru::init(argc, argv);
  this->window = CreateScope<Window>(WindowProps());
  this->isRunning = true;
}

void ALinkApplication::InternalEvents() {
  this->window->OnUpdate();
}
}  // namespace ALinkEngine
