#ifndef VULKANTEST_TRIANGLEAPP_HPP
#define VULKANTEST_TRIANGLEAPP_HPP

#include <vkfw/vkfw.hpp>

#include "Definitions.hpp"

class TriangleApp {
public:
#ifdef NDEBUG
    static constexpr const Bool EnableValidationLayers = false;
#else // NDEBUG
#define TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    static constexpr const UInt32 ValidationLayerCount = 1;
    static constexpr const Char8 *ValidationLayers[] = {
            "VK_LAYER_KHRONOS_validation"
    };
#endif // NDEBUG
    static constexpr const Char8 AppName[] = "Triangle App";
    static constexpr const UInt32 WindowWidth = 1920 / 4;
    static constexpr const UInt32 WindowHeight = 1080 / 4;

public:
    TriangleApp();

    Void run();

    Void stop();

private:
    vkfw::Window window;
    vk::Instance vulkan;
    UInt64 count;

private:
    inline Void initWindow();

    inline Void initVulkan();

#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    static inline Bool checkValidationLayerSupport();
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED

private:
    static Void error_window_callback(UInt32 errorCode, const Char8 *description);

    static Void key_window_callback(
            const vkfw::Window &window, vkfw::Key key, UInt32 scancode, vkfw::KeyAction action,
            const vkfw::ModifierKeyFlags &modifiers
    );
};

#endif // VULKANTEST_TRIANGLEAPP_HPP
