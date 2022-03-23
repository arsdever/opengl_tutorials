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
        static constexpr size_t id_length = 8;
        std::string result;
        result.resize(id_length);
        static constexpr char symbols[] = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

        std::random_device                 r;
        std::default_random_engine         e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, sizeof(symbols) - 2); // decrease to ignore null terminator

        for (int i = 0; i < id_length; ++i)
            {
                size_t idx  = uniform_dist(e1);
                result[ i ] = char(symbols[ idx ]);
            }

        return result;
    }
} // namespace utils