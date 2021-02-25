#ifndef ALINKENGINE_CORE_LOGGER_H_
#define ALINKENGINE_CORE_LOGGER_H_
#include <loguru.hpp>


#define ALINK_LOG_INFO(...)  LOG_F(INFO, __VA_ARGS__)
#define ALINK_LOG_WARN(...)  LOG_F(WARNING, __VA_ARGS__)
#define ALINK_LOG_ERROR(...) LOG_F(ERROR, __VA_ARGS__)



#endif  // ALINKENGINE_CORE_LOGGER_H_
