#include "TriangleApp.hpp"
#include <iostream>

Int32 main() {
  vkfw::init();
  try {
    TriangleApp app;
    app.run();
    app.stop();
  } catch (const std::system_error &err) {
    std::cout << "Error: " << err.what() << '\n';
    return 1;
  }
  vkfw::terminate();
  return 0;
}
