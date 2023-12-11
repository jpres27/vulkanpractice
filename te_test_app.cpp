#include "te_test_app.hpp"

#include <stdexcept>

namespace te {

TeTestApp::TeTestApp() {
    create_pipeline_layout();
    create_pipeline();
    create_command_buffers();
}

TeTestApp::~TeTestApp() {
    vkDestroyPipelineLayout(te_device.device(), pipeline_layout, nullptr);
}

void TeTestApp::run() {
    while(!te_window.should_close()) {
        glfwPollEvents();
    }
}

void TeTestApp::create_pipeline_layout() {
    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 0;
    pipeline_layout_info.pPushConstantRanges = nullptr;
    if(vkCreatePipelineLayout(te_device.device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout");
    }
}

void TeTestApp::create_pipeline() {
    auto pipeline_config = TePipeline::default_pipeline_config(te_swap_chain.width(), te_swap_chain.height());
    pipeline_config.render_pass = te_swap_chain.getRenderPass();
    pipeline_config.pipeline_layout = pipeline_layout;
    te_pipeline = std::make_unique<TePipeline>(te_device, VERTPATH, FRAGPATH, pipeline_config);
}

void TeTestApp::create_command_buffers() {

}

void TeTestApp::draw_frame() {

}

} // namespace te