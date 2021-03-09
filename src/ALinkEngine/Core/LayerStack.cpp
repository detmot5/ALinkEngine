#include "alinkpch.h"
#include "LayerStack.h"

namespace ALink {
LayerStack::LayerStack() : lastLayerIndex(0) {}

LayerStack::~LayerStack() {
  for (Layer* layer : this->layers) delete layer;
}

void LayerStack::AddLayer(Layer* layer) {
  this->layers.emplace(this->layers.begin() + this->lastLayerIndex, layer);
  this->lastLayerIndex++;
}

void LayerStack::AddOverlay(Layer* overlay) {
  this->layers.emplace_back(overlay);
}

void LayerStack::DeleteLayer(Layer* layer) {
  auto position = std::find(this->layers.begin(), this->layers.end(), layer);
  if (position != layers.end()) {
    this->layers.erase(position);
    this->lastLayerIndex--;
  }
}

void LayerStack::DeleteOverlay(Layer* overlay) {
  auto position = std::find(this->layers.begin(), this->layers.end(), overlay);
  if (position != layers.end()) this->layers.erase(position);
}
}  // namespace ALink
