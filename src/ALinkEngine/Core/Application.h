#ifndef ALINKENGINE_CORE_APPLICATION_H_
#define ALINKENGINE_CORE_APPLICATION_H_

namespace ALinkEngine {
  
class ALinkApplication {
 public:
  ALinkApplication();
  virtual ~ALinkApplication();
  void InternalInit(int argc, char* argv[]);
  
  virtual void Init() {}
  virtual void ShutDown() {}
  virtual void Run() {}
};


ALinkApplication* CreateApplication();
}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_APPLICATION_H_
