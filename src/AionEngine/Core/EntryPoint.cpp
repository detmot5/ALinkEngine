#include "EntryPoint.h"

int main(void) {
  auto entry = AionEngine::CreateEntry();
  entry->run();
  delete entry;
}
