#pragma once

#include "te_window.hpp"

namespace te {
class TeTestApp {

    public: 
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();
    
    private:
        TeWindow te_window{WIDTH, HEIGHT, "Ave, Vulkan"};
};    

} // namespace te