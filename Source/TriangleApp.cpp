#include "TriangleApp.hpp"

#include <vkfw/vkfw.hpp>
#include <vulkan/vulkan.hpp>
#include <iostream>

TriangleApp::TriangleApp()
        : count(0) {
    this->initWindow();
    this->initVulkan();
}

inline Void TriangleApp::initWindow() {
    vkfw::init();
    vkfw::setErrorCallback((GLFWerrorfun)TriangleApp::error_window_callback);
    vkfw::WindowHints winHints; // TODO Redo this.
    winHints.resizable = vkfw::eFalse;
    winHints.clientAPI = vkfw::ClientAPI::eNone;
    this->window = vkfw::createWindow(
            TriangleApp::WindowWidth, TriangleApp::WindowHeight, TriangleApp::AppName,
            winHints
    );
    this->window.callbacks()->on_key = TriangleApp::key_window_callback;
}

inline Void TriangleApp::initVulkan() {
#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    if (!TriangleApp::checkValidationLayerSupport()) {
        throw std::runtime_error("Validation layers are not available.");
    }
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    vk::ApplicationInfo appInfo(
            TriangleApp::AppName,
    VK_MAKE_VERSION(1, 0, 0), "Undefined", VK_MAKE_VERSION(0, 0, 0),
            VK_API_VERSION_1_0
    );
    UInt32 extCount;
    const Char8 **exts = vkfw::getRequiredInstanceExtensions(&extCount);
#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    vk::InstanceCreateInfo vkCreateInfo(
            vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR, &appInfo, TriangleApp::ValidationLayerCount,
            TriangleApp::ValidationLayers, extCount, exts, nil
    );
#else // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    vk::InstanceCreateInfo vkCreateInfo(
            vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR, &appInfo, 0, nil, extCount, exts, nil
    );
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
    this->vulkan = vk::createInstance(vkCreateInfo);
}

#ifdef TRIANGLE_APP_VALIDATION_LAYERS_ENABLED
inline Bool TriangleApp::checkValidationLayerSupport() {
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
    for (UInt32 i = 0; i < TriangleApp::ValidationLayerCount; ++i) {
        for (UInt32 j = 0; j < layerCount; ++j) {
            if (strcmp(TriangleApp::ValidationLayers[i], availLayers[j].layerName) == 0) {
                goto FOUND;
            }
        }
    }
    return false;
FOUND:
    return true;
}
#endif // TRIANGLE_APP_VALIDATION_LAYERS_ENABLED

Void TriangleApp::run() {
    while (!this->window.shouldClose()) {
        std::cout << "Count: " << this->count << '\n';
        vkfw::pollEvents();
        this->count++;
    }
}

Void TriangleApp::stop() {
    this->vulkan.destroy();
    this->window.destroy();
    vkfw::terminate();
}

Void TriangleApp::error_window_callback(UInt32 errorCode, const Char8 *description = "???") {
    std::cout << "Error (" << errorCode << "): " << description << '\n';
}

Void TriangleApp::key_window_callback(
        const vkfw::Window &window, vkfw::Key key, UInt32,
        vkfw::KeyAction action, const vkfw::ModifierKeyFlags &
) {
    if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress) {
        window.setShouldClose(true);
    }
}
