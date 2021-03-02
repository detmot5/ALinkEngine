#ifndef ALINKENGINE_CORE_LAYERSTACK_H_
#define ALINKENGINE_CORE_LAYERSTACK_H_

#include "Core/Layer.h"
#include "alinkpch.h"

namespace ALinkEngine {

using LayerStackDataStorage = std::vector<Layer*>; 

class LayerStack {
 public:
  LayerStack();
  ~LayerStack();
  void AddLayer(Layer* layer);
  void AddOverlay(Layer* overlay);
  void DeleteLayer(Layer* layer);
  void DeleteOverlay(Layer* overlay);
  LayerStackDataStorage::iterator begin() { return layers.begin(); }
  LayerStackDataStorage::iterator end() { return layers.end(); }
  LayerStackDataStorage::reverse_iterator reverseBegin() { return layers.rbegin(); }
  LayerStackDataStorage::reverse_iterator reverseEnd() { return layers.rend(); }

 private:
  LayerStackDataStorage layers;
  LayerStackDataStorage::iterator lastLayerPosition;
};

}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_LAYERSTACK_H_
