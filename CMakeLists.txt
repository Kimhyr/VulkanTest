cmake_minimum_required(VERSION 3.23)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(VulkanTest Main.cpp Definitions.hpp TriangleApp.hpp TriangleApp.cpp)

target_link_libraries(VulkanTest PUBLIC
        "D:/VulkanSDK/1.3.231.1/Lib/vulkan-1.lib"
        D:/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a)
target_include_directories(VulkanTest PUBLIC "${PROJECT_BINARY_DIR}"
        "D:/VulkanSDK/1.3.231.1/Include"
        "D:/glfw-3.3.8.bin.WIN64/include")
