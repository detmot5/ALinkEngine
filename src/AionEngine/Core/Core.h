#ifndef AIONENGINE_CORE_CORE_H_
#define AIONENGINE_CORE_CORE_H_

#if defined(__MINGW32__) || defined(WIN32)
#define AION_PLATFORM_WINDOWS  1
#elif defined(__linux__)
#define AION_PLATFORM_LINUX   1
#elif defined(__APPLE__)
#error This day Aion keeps Apple away!
#endif

#include <csignal>
#define AION_DEBUGBREAK() raise(SIGTRAP)

#endif  // AIONENGINE_CORE_CORE_H_
