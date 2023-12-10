#pragma once

#include "te_window.hpp"
#include "te_pipeline.hpp"
#include "te_device.hpp"

#define VERTPATH "shaders/test_shader.vert.spv"
#define FRAGPATH "shaders/test_shader.frag.spv"

namespace te {
class TeTestApp {

    public: 
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

    private:
        TeWindow te_window { WIDTH, HEIGHT, "Ave!" };
        TeDevice te_device { te_window };
        TePipeline te_pipeline{ te_device,  
                                VERTPATH, 
                                FRAGPATH, 
                                TePipeline::default_pipeline_config(WIDTH, HEIGHT) };
};    

} // namespace te