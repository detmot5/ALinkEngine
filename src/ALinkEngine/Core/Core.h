#ifndef ALINKENGINE_CORE_CORE_H_
#define ALINKENGINE_CORE_CORE_H_


#if defined(__MINGW32__) || defined(WIN32)
#define ALINK_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define ALINK_PLATFORM_LINUX 1
#elif defined(__APPLE__)
#error This day ALink keeps Apple away!
#endif

#ifdef ALINK_DEBUG
#ifdef ALINK_PLATFORM_WINDOWS
#define ALINK_DEBUGBREAK() __debugbreak()
#else
#include <csignal>
#define ALINK_DEBUGBREAK() raise(SIGTRAP)
#endif
#define ALINK_ASSERT(x, ...)                    \
  if (!(x)) {                                   \
    ALINK_LOG_ERROR("ALINK ASSERTION FAILED!"); \
    ALINK_LOG_ERROR(__VA_ARGS__);               \
    ALINK_DEBUGBREAK();                         \
  }
#define ALINK_ENGINE_ASSERT(x, ...)                              \
  if (!(x)) {                                                    \
    ALINK_ENGINE_LOG_CRITICAL("ALINK ENGINE ASSERTION FAILED!"); \
    ALINK_ENGINE_LOG_CRITICAL(__VA_ARGS__);                      \
    ALINK_DEBUGBREAK();                                          \
  }
#else
#define ALINK_DEBUGBREAK()
#define ALINK_ASSERT(x, ...)
#define ALINK_ENGINE_ASSERT(x, ...)
#endif

#define ALINK_BIND_EVENT_CALLBACK(fn)                       \
  [this](auto&&... args) -> decltype(auto) {                \
    return this->fn(std::forward<decltype(args)>(args)...); \
  }

#define BIT(x) (1 << x)

#endif  // ALINKENGINE_CORE_CORE_H_
