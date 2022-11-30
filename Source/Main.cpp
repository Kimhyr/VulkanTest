#include <iostream>

#include "Triangle/Application.hpp"

Int32 main() {
    try {
        Triangle::Application app;
        app.run();
    }
    catch (const auto &err) {
        std::cout << "Error: " << err.what() << '\n';
        return 1;
    }
    return 0;
}
