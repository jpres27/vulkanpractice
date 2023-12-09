#pragma once

#include "te_window.hpp"
#include "te_pipeline.hpp"

#define VERTPATH "shaders/test_shader.vert.spv"
#define FRAGPATH "shaders/test_shader.frag.spv"

namespace te {
class TeTestApp {

    public: 
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

    private:
        TeWindow te_window{WIDTH, HEIGHT, "Ave, Vulkan"};
        TePipeline te_pipeline{ VERTPATH, FRAGPATH };
};    

} // namespace te