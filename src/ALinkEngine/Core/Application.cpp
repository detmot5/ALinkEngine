#include "Application.h"
#include "alinkpch.h"


namespace ALinkEngine {
  ALinkApplication::ALinkApplication() {
    
  }

  ALinkApplication::~ALinkApplication() {

  }
  
  void ALinkApplication::InternalInit(int argc, char* argv[])  {
    loguru::init(argc, argv);
  }
}

