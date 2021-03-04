#ifndef ALINKENGINE_CORE_LOGGER_H_
#define ALINKENGINE_CORE_LOGGER_H_
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "alinkpch.h"

namespace ALinkEngine {
class Logger {
 public:
  static inline void Init() {
    spdlog::set_pattern("%^[%n - %l] [Thread - %t] - %v%$");
    engineLogger = spdlog::stdout_color_mt("ALinkEngine");
    engineLogger->set_level(spdlog::level::trace);
    applicationLogger = spdlog::stdout_color_mt("ALinkApp");
    applicationLogger->set_level(spdlog::level::trace);
  }
  static inline std::shared_ptr<spdlog::logger>& GetEngineLogger() {
    return engineLogger;
  }
  static inline std::shared_ptr<spdlog::logger>& GetAppLogger() {
    return applicationLogger;
  }

 private:
  static inline std::shared_ptr<spdlog::logger> engineLogger;
  static inline std::shared_ptr<spdlog::logger> applicationLogger;
};

}  // namespace ALinkEngine

// Core log macros
#define ALINK_ENGINE_LOG_TRACE(...)    ::ALinkEngine::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define ALINK_ENGINE_LOG_INFO(...)     ::ALinkEngine::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define ALINK_ENGINE_LOG_WARN(...)     ::ALinkEngine::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define ALINK_ENGINE_LOG_ERROR(...)    ::ALinkEngine::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define ALINK_ENGINE_LOG_CRITICAL(...) ::ALinkEngine::Logger::GetEngineLogger()->critical(__VA_ARGS__)

// Client log macros
#define ALINK_LOG_TRACE(...)           ::ALinkEngine::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define ALINK_LOG_INFO(...)            ::ALinkEngine::Logger::GetAppLogger()->info(__VA_ARGS__)
#define ALINK_LOG_WARN(...)            ::ALinkEngine::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define ALINK_LOG_ERROR(...)           ::ALinkEngine::Logger::GetAppLogger()->error(__VA_ARGS__)
#define ALINK_LOG_CRITICAL(...)        ::ALinkEngine::Logger::GetAppLogger()->critical(__VA_ARGS__)


#endif  // ALINKENGINE_CORE_LOGGER_H_
