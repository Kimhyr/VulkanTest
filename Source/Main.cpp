#include <iostream>

#include "Triangle/Application.hpp"

Int32 main() {
    try {
        Triangle::Application app;
        app.run();
        app.stop();
    } catch (const std::system_error &err) {
        std::cout << "Error: " << err.what() << '\n';
        return 1;
    }
    return 0;
}
