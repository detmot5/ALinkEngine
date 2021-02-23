#include "EntryPoint.h"

int main(void) {
  auto entry = ALinkEngine::createEntry();
  entry->run();
  delete entry;
}
