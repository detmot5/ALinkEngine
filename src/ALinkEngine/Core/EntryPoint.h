#ifndef ALINKENGINE_CORE_ENTRYPOINT_H_
#define ALINKENGINE_CORE_ENTRYPOINT_H_

namespace ALinkEngine {
  
class ALinkEntryPoint {
 public:
  ALinkEntryPoint() {}
  ~ALinkEntryPoint() {}
  virtual void run() = 0;
};


ALinkEntryPoint* createEntry();
}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_ENTRYPOINT_H_
