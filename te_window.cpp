#include "te_window.hpp"

#include <stdexcept>

namespace te {

TeWindow::TeWindow(int w, int h, std::string name) : width{w}, height{h}, window_name{name} {
    init_window();
}

TeWindow::~TeWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void TeWindow::create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
}

void TeWindow::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
}
} // namespace te