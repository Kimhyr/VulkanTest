CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

SET(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++")
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_BINARY_DIR "E:/Projects/VulkanTest/Output")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")

PROJECT(VulkanTest)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror -O3)

ADD_EXECUTABLE(VulkanTest Source/Main.cpp Source/Definitions.hpp Source/Triangle/Application.hpp Source/Triangle/Application.cpp Source/Utils.hpp)

TARGET_LINK_LIBRARIES(
        VulkanTest PUBLIC
        "D:/VulkanSDK/1.3.231.1/Lib/vulkan-1.lib"
        D:/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a
)
TARGET_INCLUDE_DIRECTORIES(
        VulkanTest PUBLIC "${PROJECT_BINARY_DIR}"
        "D:/VulkanSDK/1.3.231.1/Include"
        "D:/glfw-3.3.8.bin.WIN64/include"
        "D:/gmtl-0.6.1/gmtl"
)
