#ifndef ALINKENGINE_CORE_LAYER_H_
#define ALINKENGINE_CORE_LAYER_H_

#include "Core/Core.h"
#include "Events/Event.h"
#include "alinkpch.h"

namespace ALinkEngine {
class Layer {
 public:
  explicit Layer(const std::string& name = "Layer") 
    : debugName(name) {}
  virtual ~Layer() {}

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event& event) {}

  inline const std::string GetName() const { return debugName; }
 private:
  std::string debugName;
};
}  // namespace ALinkEngine


#endif  // ALINKENGINE_CORE_LAYER_H_
