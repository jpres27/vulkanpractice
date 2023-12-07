#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace te {

    class TeWindow {
        public:
            TeWindow(int w, int h, std::string name);
            ~TeWindow();

        private:

            void initWindow();

            int width;
            int height;

            //DO NOT USE STD::STRING - REPLACE THIS LATER
            std::string window_name;
            GLFWwindow *window;
    };
} // namescape te