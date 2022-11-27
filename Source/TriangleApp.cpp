#include "TriangleApp.hpp"

#include <iostream>

TriangleApp::TriangleApp()
    : window(vkfw::createWindow(TriangleApp::WindowWidth, TriangleApp::WindowHeight, TriangleApp::WindowName)),
      count(0) {
  vkfw::setErrorCallback((GLFWerrorfun)TriangleApp::error_window_callback);
  this->window.callbacks()->on_key = TriangleApp::key_window_callback;
}

Void TriangleApp::run() {
  while (!this->window.shouldClose()) {
    vkfw::pollEvents();
    this->count++;
  }
}

Void TriangleApp::stop() {
  this->window.destroy();
}

Void TriangleApp::error_window_callback(UInt32 errorCode, const Char8 *description = "???") {
  std::cout << "Error (" << errorCode << "): " << description << '\n';
}

Void TriangleApp::key_window_callback(const vkfw::Window &window, vkfw::Key key, UInt32 scancode,
                                      vkfw::KeyAction action, vkfw::ModifierKeyFlags modifiers) {
  if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress) {
    window.setShouldClose(true);
  }
}
