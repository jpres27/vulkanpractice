#include "te_pipeline.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace te {

TePipeline::TePipeline(const std::string& vert_filepath, const std::string& frag_filepath) {
    TePipeline::create_graphics_pipeline(vert_filepath, frag_filepath);
}


std::vector<char> TePipeline::read_file(const std::string& filepath) {
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};
    if(!file.is_open()) throw std::runtime_error("Failed to open file:" + filepath);

    size_t file_size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}

void TePipeline::create_graphics_pipeline(const std::string& vert_filepath, const std::string& frag_filepath) {
    auto vert_code = read_file(vert_filepath);
    auto frag_code = read_file(frag_filepath);

    std::cout << "Vertex shader code size: " << vert_code.size() << std::endl;
    std::cout << "Fragment shader code size: " << frag_code.size() << std::endl;

}



} // namespace te