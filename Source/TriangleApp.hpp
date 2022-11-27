#ifndef VULKANTEST_TRIANGLEAPP_HPP
#define VULKANTEST_TRIANGLEAPP_HPP

#include <vkfw/vkfw.hpp>

#include "Definitions.hpp"

class TriangleApp {
public:
    static constexpr const UInt32 WindowWidth = 1920 / 4;
    static constexpr const UInt32 WindowHeight = 1080 / 4;
    static constexpr const Char8 *WindowName = "Triangle App";

public:
    TriangleApp();

    Void run();

    Void stop();

private:
    vkfw::Window window;
    UInt64 count;

private:
    static Void error_window_callback(UInt32 errorCode, const Char8 *description);

    static Void key_window_callback(const vkfw::Window &window, vkfw::Key key, UInt32 scancode, vkfw::KeyAction action,
                                    vkfw::ModifierKeyFlags modifiers);
};


#endif // VULKANTEST_TRIANGLEAPP_HPP
