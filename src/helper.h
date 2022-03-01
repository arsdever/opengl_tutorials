#pragma once

#include <fstream>
#include <random>
#include <sstream>

namespace utils
{
    inline std::string load_shader_from_file(const std::string& filepath)
    {
        std::ifstream     reader(filepath);
        std::stringstream buf;
        buf << reader.rdbuf();
        return buf.str();
    }

    inline std::string generate_uid()
    {
        std::string result;
        result.resize(64);
        static constexpr char symbols[] = "1234567890qwertyuiopasdfghjklzxcvnmQWERTYUIOPASDFGHJKLZXCVBNM";

        std::random_device                 r;
        std::default_random_engine         e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, sizeof(symbols) - 1); // decrease to ignore null terminator

        for (int i = 0; i < 64; ++i)
            {
                result[ i ] = symbols[ uniform_dist(e1) ];
            }

        return result;
    }
} // namespace utils