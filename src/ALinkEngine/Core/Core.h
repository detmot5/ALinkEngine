#ifndef ALINKENGINE_CORE_CORE_H_
#define ALINKENGINE_CORE_CORE_H_

#if defined(__MINGW32__) || defined(WIN32)
#define ALINK_PLATFORM_WINDOWS  1
#elif defined(__linux__)
#define ALINK_PLATFORM_LINUX   1
#elif defined(__APPLE__)
#error This day ALink keeps Apple away!
#endif

#include <csignal>
#define ALINK_DEBUGBREAK() raise(SIGTRAP)

#endif  // ALINKENGINE_CORE_CORE_H_
