#include "te_window.hpp"

namespace te {

    TeWindow::TeWindow(int w, int h, std::string name) : width{w}, height{h}, window_name{name} {
        init_window();
    }

    TeWindow::~TeWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void TeWindow::init_window() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    }
} // namespace te