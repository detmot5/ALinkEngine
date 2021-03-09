file(GLOB imgui_src "*.cpp")
file(GLOB imgui_backend_src "backends/imgui_impl_glfw.cpp"
                            "backends/imgui_impl_opengl3.cpp")
add_library(imgui ${imgui_src} ${imgui_backend_src})
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui PUBLIC "./")
target_include_directories(imgui PUBLIC "./backends")


