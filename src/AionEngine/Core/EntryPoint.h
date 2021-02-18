#ifndef AIONENGINE_CORE_ENTRYPOINT_H_
#define AIONENGINE_CORE_ENTRYPOINT_H_

namespace AionEngine {
  
class AionEntryPoint {
 public:
  AionEntryPoint() {}
  ~AionEntryPoint() {}
  virtual void run() = 0;
};


AionEntryPoint* CreateEntry();
}  // namespace AionEngine

#endif  // AIONENGINE_CORE_ENTRYPOINT_H_
