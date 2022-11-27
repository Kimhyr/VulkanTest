#include <iostream>

#include "TriangleApp.hpp"

Int32 main() {
    try {
        TriangleApp app;
        app.run();
        app.stop();
    } catch (const std::system_error &err) {
        std::cout << "Error: " << err.what() << '\n';
        return 1;
    }
    return 0;
}
