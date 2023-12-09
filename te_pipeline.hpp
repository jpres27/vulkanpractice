#pragma once

#include <string>
#include <vector>

namespace te {

class TePipeline {
    public: 
    TePipeline(const std::string& vert_filepath, const std::string& frag_filepath);

    private:
    static std::vector<char> read_file(const std::string& filepath);

    void create_graphics_pipeline(const std::string& vert_filepath, const std::string& frag_filepath);
};


} // namespace te