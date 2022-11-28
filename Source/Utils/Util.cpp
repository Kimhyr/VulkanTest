#include "Util.hpp"

vk::Result Util::createDebugUtilsMessengerEXT(
        vk::Instance instance, const vk::DebugUtilsMessengerCreateInfoEXT *createInfo,
        const vk::AllocationCallbacks *allocator, vk::DebugUtilsMessengerEXT *debugMessenger
) {
    auto proc = (PFN_vkCreateDebugUtilsMessengerEXT)
            instance.getProcAddr("vkCreateDebugUtilsMessengerEXT");
    return proc != nil
           ? (vk::Result)proc(
                    instance, (VkDebugUtilsMessengerCreateInfoEXT *)createInfo, (VkAllocationCallbacks *)allocator,
                    (VkDebugUtilsMessengerEXT *)debugMessenger
            )
           : vk::Result::eErrorExtensionNotPresent;
}

Void Util::destroyDebugUtilsMessengerEXT(
        vk::Instance instance, vk::DebugUtilsMessengerEXT debugMessenger,
        const vk::AllocationCallbacks *allocator
) {
    auto proc = (PFN_vkDestroyDebugUtilsMessengerEXT)
            instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT");
    if (proc != nil) {
        proc(instance, debugMessenger, (VkAllocationCallbacks *)allocator);
    }
}
