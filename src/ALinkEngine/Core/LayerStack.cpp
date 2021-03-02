#include "Core/LayerStack.h"

namespace ALinkEngine {
LayerStack::LayerStack() { this->lastLayerPosition = layers.begin(); }

LayerStack::~LayerStack() {
  for (Layer* layer : this->layers) delete layer;
}

void LayerStack::AddLayer(Layer* layer) {
  this->lastLayerPosition =
      this->layers.emplace(this->lastLayerPosition, layer);
}

void LayerStack::AddOverlay(Layer* overlay) {
  this->layers.emplace_back(overlay);
}

void LayerStack::DeleteLayer(Layer* layer) {
  auto position = std::find(this->layers.begin(), this->layers.end(), layer);
  if (position != layers.end()) {
    this->layers.erase(position);
    this->lastLayerPosition--;
  }
}

void LayerStack::DeleteOverlay(Layer* overlay) {
  auto position = std::find(this->layers.begin(), this->layers.end(), overlay);
  if (position != layers.end()) this->layers.erase(position);
}
}  // namespace ALinkEngine
