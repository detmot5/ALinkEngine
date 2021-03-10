file(GLOB stb_image_src "stb/stb_image.cpp")
add_library(stb ${stb_image_src})
target_include_directories(stb PUBLIC "./")