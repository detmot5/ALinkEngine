#ifndef ALINKENGINE_CORE_CORE_H_
#define ALINKENGINE_CORE_CORE_H_

#if defined(__MINGW32__) || defined(WIN32)
#define ALINK_PLATFORM_WINDOWS  1
#elif defined(__linux__)
#define ALINK_PLATFORM_LINUX   1
#elif defined(__APPLE__)
#error This day ALink keeps Apple away!
#endif

#ifdef ALINK_DEBUG
#include <csignal>
#define ALINK_DEBUGBREAK() raise(SIGTRAP)
#define NL
#define ALINK_ASSERT(x, ...)         if (!(x)) ALINK_LOG_ERROR("Alink assertion failed!"); ALINK_LOG_ERROR(__VA_ARGS__)
#define ALINK_ENGINE_ASSERT(x, ...)  if (!(x)) { \
                                   ALINK_LOG_ERROR("Alink enigne assertion failed!"); ALINK_LOG_ERROR(__VA_ARGS__);}
                    
#else 

#endif

#endif  // ALINKENGINE_CORE_CORE_H_
