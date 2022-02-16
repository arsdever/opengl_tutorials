#pragma once

#include <fstream>
#include <sstream>

namespace utils
{
    inline std::string load_shader_from_file(const std::string& filepath)
    {
        std::ifstream reader(filepath);
        std::stringstream buf;
        buf << reader.rdbuf();
        return buf.str();
    }
}