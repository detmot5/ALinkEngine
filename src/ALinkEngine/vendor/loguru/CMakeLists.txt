add_definitions(-DLOGURU_STACKTRACES=0)
add_library(loguru "loguru.cpp")
target_include_directories(loguru PUBLIC "./")