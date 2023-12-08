#include "te_test_app.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    te::TeTestApp app {};

    app.run();
    std::cout << "Program ran" << std::endl;
    return 0;
}