#pragma once

#include <filesystem>

namespace gl
{
    class texture2d
    {
    public:
        texture2d();

        static texture2d            from_file(const std::filesystem::path& filepath);
        const std::vector<uint8_t>& data() const;
        unsigned                    width() const;
        unsigned                    height() const;

    private:
        unsigned             _width;
        unsigned             _height;
        std::vector<uint8_t> _data;
    };
} // namespace gl