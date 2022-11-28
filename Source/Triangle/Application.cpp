#include "Application.hpp"

#include <vkfw/vkfw.hpp>
#include <vulkan/vulkan.hpp>
#include <iostream>

#include "../Utils/Util.hpp"

Triangle::Application::Application()
        : count(0) {
    this->initWindow();
    this->initVulkan();
}

inline Void Triangle::Application::initWindow() {
    vkfw::init();
    vkfw::setErrorCallback((GLFWerrorfun)Triangle::Application::error_window_callback);
    vkfw::WindowHints winHints; // TODO Redo zthis.
    winHints.resizable = vkfw::eFalse;
    winHints.clientAPI = vkfw::ClientAPI::eNone;
    this->window = vkfw::createWindow(
            Triangle::Application::WindowWidth, Triangle::Application::WindowHeight,
            Triangle::Application::AppName, winHints
    );
    this->window.callbacks()->on_key = Triangle::Application::key_window_callback;
}

inline Void Triangle::Application::initVulkan() {
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    if (!Triangle::Application::checkValidationLayerSupport()) {
        throw std::runtime_error("Validation layers are not available.");
    }
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    vk::ApplicationInfo appInfo(
            Triangle::Application::AppName, VK_MAKE_VERSION(1, 0, 0),
            "Undefined", VK_MAKE_VERSION(0, 0, 0),
            VK_API_VERSION_1_0
    );
    std::vector<const Char8 *> exts = Triangle::Application::getRequiredExtensions();
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    vk::InstanceCreateInfo vkCreateInfo(
            vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
            &appInfo, Triangle::Application::ValidationLayerCount,
            Triangle::Application::ValidationLayers, exts.size(),
            exts.data(), nil
    );
#else // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    vk::InstanceCreateInfo vkCreateInfo(
            vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR, &appInfo, 0, nil, exts.size(), exts.data(), nil
    );
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    this->vulkan = vk::createInstance(vkCreateInfo);
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    this->initDebugMessenger();
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
}

#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
inline Void Triangle::Application::initDebugMessenger() {
    vk::DebugUtilsMessengerCreateInfoEXT createInfo(
            {}, vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            Triangle::Application::debug_callback
    );
    if (Util::createDebugUtilsMessengerEXT(this->vulkan, &createInfo, nil, &debugMessenger) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to initiate  a debug messenger.");
    }
}
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED

#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
inline Bool Triangle::Application::checkValidationLayerSupport() {
    UInt32 layerCount = 0;
    switch (vk::enumerateInstanceLayerProperties(&layerCount, nil)) {
    case vk::Result::eIncomplete:
    case vk::Result::eSuccess:
        break;
    default:
        throw std::runtime_error("Failed to enumerate instance layer properties.");
    }
    vk::LayerProperties *availLayers = new vk::LayerProperties[layerCount];
    switch (vk::enumerateInstanceLayerProperties(&layerCount, availLayers)) {
    case vk::Result::eIncomplete:
    case vk::Result::eSuccess:
        break;
    default:
        throw std::runtime_error("Failed to enumerate instance layer properties.");
    }
    for (UInt32 i = 0; i < Triangle::Application::ValidationLayerCount; ++i) {
        for (UInt32 j = 0; j < layerCount; ++j) {
            if (strcmp(Triangle::Application::ValidationLayers[i], availLayers[j].layerName) == 0) {
                goto FOUND;
            }
        }
    }
    return false;
FOUND:
    return true;
}
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED

inline std::vector<const Char8 *> Triangle::Application::getRequiredExtensions() {
    UInt32 gextCount = 0;
    const Char8 **gexts;
    gexts = vkfw::getRequiredInstanceExtensions(&gextCount);
    std::vector<const Char8 *> exts(gexts, gexts + gextCount);
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    return exts;
}

Void Triangle::Application::run() {
    while (!this->window.shouldClose()) {
        std::cout << "[Info] Count: " << this->count << '\n';
        vkfw::pollEvents();
        this->count++;
    }
    this->stop();
}

Void Triangle::Application::stop() {
#ifdef TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    Util::destroyDebugUtilsMessengerEXT(this->vulkan, this->debugMessenger);
#endif // TRIANGLE_APPLICATION_VALIDATION_LAYERS_ENABLED
    this->vulkan.destroy();
    this->window.destroy();
    vkfw::terminate();
}

Void Triangle::Application::error_window_callback(UInt32 errorCode, const Char8 *description = "???") {
    std::cout << "Error (" << errorCode << "): " << description << '\n';
}

Void Triangle::Application::key_window_callback(
        const vkfw::Window &window, vkfw::Key key,
        UInt32, vkfw::KeyAction action,
        const vkfw::ModifierKeyFlags &
) {
    if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress) {
        window.setShouldClose(true);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL Triangle::Application::debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT,
        const VkDebugUtilsMessengerCallbackDataEXT *callbackData, Void *
) {
    switch ((vk::DebugUtilsMessageSeverityFlagBitsEXT)severity) {
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
        std::cout << "[Error] ";
        break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
        std::cout << "[Info] ";
        break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
        std::cout << "[Verbose] ";
        break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
        std::cout << "[Warning] ";
        break;
    }
    std::cerr << "Validation layer: " << callbackData->pMessage << '\n';
    return 0;
}
