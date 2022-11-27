cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR "E:/Projects/VulkanTest/Output")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")

project(VulkanTest)

add_compile_options(-Wall -Wextra -Werror -O3)

add_executable(VulkanTest Source/Main.cpp Source/Definitions.hpp Source/TriangleApp.hpp Source/TriangleApp.cpp)

target_link_libraries(VulkanTest PUBLIC
        "D:/VulkanSDK/1.3.231.1/Lib/vulkan-1.lib"
        D:/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a)
target_include_directories(VulkanTest PUBLIC "${PROJECT_BINARY_DIR}"
        "D:/VulkanSDK/1.3.231.1/Include"
        "D:/glfw-3.3.8.bin.WIN64/include")
