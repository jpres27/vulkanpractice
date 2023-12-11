#pragma once

#include <string>
#include <vector>
#include "te_device.hpp"

namespace te {

struct pipeline_config_info {
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
    VkPipelineRasterizationStateCreateInfo rasterization_info;
    VkPipelineMultisampleStateCreateInfo multisample_info;
    VkPipelineColorBlendAttachmentState color_blend_attachment;
    VkPipelineColorBlendStateCreateInfo color_blend_info;
    VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
    VkPipelineLayout pipeline_layout = nullptr;
    VkRenderPass render_pass = nullptr;
    uint32_t subpass = 0;
};

class TePipeline {
public: 
    TePipeline(TeDevice &device, const std::string& vert_filepath, const std::string& frag_filepath, const pipeline_config_info pipe_ci);
    ~TePipeline();

    TePipeline(const TePipeline&) = delete;
    void operator=(const TePipeline&) = delete;

    static pipeline_config_info default_pipeline_config(uint32_t width, uint32_t height);

private:
    static std::vector<char> read_file(const std::string& filepath);

    void create_graphics_pipeline(const std::string& vert_filepath, const std::string& frag_filepath, const pipeline_config_info pipe_ci);

    void create_shader_module(const std::vector<char>& shader_program, VkShaderModule* shader_module);

    TeDevice& te_device;
    VkPipeline gfx_pipeline;
    VkShaderModule vert_shader_module;
    VkShaderModule frag_shader_module;
};


} // namespace te