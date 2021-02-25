file(GLOB loguru_src "loguru/*.cpp")
add_definitions(-DLOGURU_STACKTRACES=0)


add_library(vendor ${loguru_src})
