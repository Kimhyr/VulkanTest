#ifndef VULKANTEST_TRIANGLE_APPLICATION_HPP
#define VULKANTEST_TRIANGLE_APPLICATION_HPP

#include <vkfw/vkfw.hpp>

#include "../Definitions.hpp"

namespace Triangle {
    class Application {
    public:
#ifdef NDEBUG
        // static constexpr const Bool EnableValidationLayers = false;
#else // NDEBUG
#define TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
        static constexpr
        const UInt32 ValidationLayerCount = 1;

        static constexpr
        const Char8 *ValidationLayers[] = {
                "VK_LAYER_KHRONOS_validation"
        };
#endif // NDEBUG
        static constexpr
        const Char8 AppName[] = "Triangle App";

        static constexpr
        const UInt32 WindowWidth = 1920 / 2;

        static constexpr
        const UInt32 WindowHeight = 1080 / 2;

    public:
        Application();

        Void run();

        inline
        Void stop();

    private:
        vkfw::Window window;
        vk::Instance vulkan;
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
        vk::DebugUtilsMessengerEXT debugMessenger;
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
        UInt64 count;

    private:
        inline
        Void initWindow();

        inline
        Void initVulkan();

#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
        inline
        Void initDebugMessenger();

        inline static
        Bool checkValidationLayerSupport();
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED

        inline static
        std::vector<const Char8 *> getRequiredExtensions();

    private:
        static
        Void error_window_callback(UInt32 errorCode, const Char8 *description);

        static
        Void key_window_callback(
                const vkfw::Window &window, vkfw::Key key,
                UInt32 scancode, vkfw::KeyAction action,
                const vkfw::ModifierKeyFlags &modifiers
        );

        VKAPI_ATTR VKAPI_CALL static
        VkBool32 debug_callback(
                VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type,
                const VkDebugUtilsMessengerCallbackDataEXT *callbackData, Void *userData
        );
    };
} // namespace Triangle


#endif // VULKANTEST_TRIANGLE_APPLICATION_HPP
