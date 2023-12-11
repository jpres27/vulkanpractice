#pragma once

#include "te_window.hpp"
#include "te_pipeline.hpp"
#include "te_device.hpp"
#include "te_swap_chain.hpp"

#include <memory>
#include <vector>

#define VERTPATH "shaders/test_shader.vert.spv"
#define FRAGPATH "shaders/test_shader.frag.spv"

namespace te {
class TeTestApp {

public: 
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    TeTestApp();
    ~TeTestApp();

    TeTestApp(const TeTestApp &) = delete;
    TeTestApp &operator=(const TeTestApp &) = delete;

    void run();

private:
    void create_pipeline_layout();
    void create_pipeline();
    void create_command_buffers();
    void draw_frame();

    TeWindow te_window { WIDTH, HEIGHT, "Ave!" };
    TeDevice te_device { te_window };
    TeSwapChain te_swap_chain {te_device, te_window.getExtent()};
    std::unique_ptr<TePipeline> te_pipeline;
    VkPipelineLayout pipeline_layout;
    std::vector<VkCommandBuffer> command_buffers;
};    

} // namespace te