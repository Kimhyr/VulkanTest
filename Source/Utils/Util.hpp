#ifndef VULKANTEST_UTILS_UTIL_HPP
#define VULKANTEST_UTILS_UTIL_HPP

#include <vulkan/vulkan.hpp>

#include "../Definitions.hpp"

namespace Util {
    vk::Result createDebugUtilsMessengerEXT(
            vk::Instance instance, const vk::DebugUtilsMessengerCreateInfoEXT *createInfo,
            const vk::AllocationCallbacks *allocator, vk::DebugUtilsMessengerEXT *debugMessenger
    );

    Void destroyDebugUtilsMessengerEXT(
            vk::Instance instance, vk::DebugUtilsMessengerEXT debugMessenger,
            const vk::AllocationCallbacks *allocator = nil
    );
} // namespace Util


#endif // VULKANTEST_UTILS_UTIL_HPP
