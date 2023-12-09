#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace te {

class TeWindow {
    public:
        TeWindow(int w, int h, std::string name);
        ~TeWindow();

        TeWindow(const TeWindow &) = delete;
        TeWindow &operator=(const TeWindow &) = delete;

        inline bool should_close() {
            return glfwWindowShouldClose(window);
        }

        void create_window_surface(VkInstance instance, VkSurfaceKHR *surface);

    private:

        void init_window();

        int width;
        int height;

        //DO NOT USE STD::STRING - REPLACE THIS LATER
        std::string window_name;
        GLFWwindow *window;
};
} // namescape te