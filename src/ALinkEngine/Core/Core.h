#ifndef ALINKENGINE_CORE_CORE_H_
#define ALINKENGINE_CORE_CORE_H_
#include <memory>
#include <utility>

#if defined(__MINGW32__) || defined(WIN32)
#define ALINK_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define ALINK_PLATFORM_LINUX 1
#elif defined(__APPLE__)
#error This day ALink keeps Apple away!
#endif

#ifdef ALINK_DEBUG
#include <csignal>
#define ALINK_DEBUGBREAK() raise(SIGTRAP)
#define ALINK_ASSERT(x, ...)                    \
  if (!(x)) {                                   \
    ALINK_LOG_ERROR("ALINK ASSERTION FAILED!"); \
    ALINK_LOG_ERROR(__VA_ARGS__)                \
  }
#define ALINK_ENGINE_ASSERT(x, ...)                   \
  if (!(x)) {                                         \
    ALINK_LOG_ERROR("ALINK ENGINE ASSERTION FAILED!"); \
    ALINK_LOG_ERROR(__VA_ARGS__);                     \
  }
#else
#define ALINK_ASSERT(x, ...)
#define ALINK_ENGINE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace ALinkEngine {

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_CORE_H_
