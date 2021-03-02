#ifndef ALINKENGINE_CORE_ENTRYPOINT_H_
#define ALINKENGINE_CORE_ENTRYPOINT_H_
#include "Application.h"

int main(int argc, char* argv[]) {
  auto app = ALinkEngine::CreateApplication();
  app->InternalInit(argc, argv);
  app->Init();
  while (app->IsRunning()) {
    app->InternalEvents();
    app->Run();
  }
  app->ShutDown();
  delete app;
}



#endif  // ALINKENGINE_CORE_ENTRYPOINT_H_
