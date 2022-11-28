#ifndef VULKANTEST_TRIANGLE_APPLICATION_HPP
#define VULKANTEST_TRIANGLE_APPLICATION_HPP

#include <vkfw/vkfw.hpp>

#include "../Definitions.hpp"
#include "../Utils.hpp"

namespace Triangle {
    class Application {
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
        Application();

        Void run();

        Void stop();

    private:
        vkfw::Window window;
        vk::Instance vulkan;
#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
        vk::DebugUtilsMessengerEXT debugMessenger;
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
        UInt64 count;

    private:
        inline Void initWindow();

        inline Void initVulkan();

#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
        inline Void initDebugMessenger();
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED

#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
        inline static inline Bool checkValidationLayerSupport();
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED

        inline static std::vector<const Char8 *> getRequiredExtensions();

    private:
        static Void error_window_callback(UInt32 errorCode, const Char8 *description);

        static Void key_window_callback(
                const vkfw::Window &window, vkfw::Key key,
                UInt32 scancode, vkfw::KeyAction action,
                const vkfw::ModifierKeyFlags &modifiers
        );

        template<typename UserDataT>
        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(
                vk::DebugUtilsMessageSeverityFlagBitsEXT severity, vk::DebugUtilsMessageTypeFlagsEXT type,
                const vk::DebugUtilsMessengerCallbackDataEXT *callbackData, UserDataT userData
        );
    };
} // namespace Triangle


#endif // VULKANTEST_TRIANGLE_APPLICATION_HPP
