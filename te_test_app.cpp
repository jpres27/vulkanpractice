#include "te_test_app.hpp"

#include <stdexcept>
#include <array>

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
        draw_frame();
    }
    vkDeviceWaitIdle(te_device.device());
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
    command_buffers.resize(te_swap_chain.imageCount());
    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandPool = te_device.getCommandPool();
    alloc_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());
    if(vkAllocateCommandBuffers(te_device.device(), &alloc_info, command_buffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate command buffer");
    }

    for(int i = 0; i < command_buffers.size(); i++) {
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(command_buffers[i], &begin_info) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer");
        }

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = te_swap_chain.getRenderPass();
        render_pass_info.framebuffer = te_swap_chain.getFrameBuffer(i);
        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = te_swap_chain.getSwapChainExtent();

        std::array<VkClearValue, 2> clear_values{};
        clear_values[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
        clear_values[1].depthStencil = {1.0f, 0};

        render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
        render_pass_info.pClearValues = clear_values.data();

        vkCmdBeginRenderPass(command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        te_pipeline->bind(command_buffers[i]);
        vkCmdDraw(command_buffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(command_buffers[i]);
        if(vkEndCommandBuffer(command_buffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer");
        }
    }

}

void TeTestApp::draw_frame() {
    uint32_t image_index;
    auto result = te_swap_chain.acquireNextImage(&image_index);
    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to acquire swap chain image");
    }
    result = te_swap_chain.submitCommandBuffers(&command_buffers[image_index], &image_index);
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swap chain image");
    }
}

} // namespace te