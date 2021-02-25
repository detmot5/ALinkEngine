#ifndef ALINKENGINE_CORE_ENTRYPOINT_H_
#define ALINKENGINE_CORE_ENTRYPOINT_H_
#include "Application.h"

int main(int argc, char* argv[]) {

  auto entry = ALinkEngine::CreateApplication();
  entry->InternalInit(argc, argv);
  entry->Init();
  
  entry->Run();
  
  entry->ShutDown();
  delete entry;
}



#endif  // ALINKENGINE_CORE_ENTRYPOINT_H_
