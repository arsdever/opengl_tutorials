#pragma once

#include <filesystem>
#include <vector>

#include "shader.h"

class shader_prog
{
public:
    shader_prog();
    void         load_shader(const std::filesystem::path& path);
    void         link();
    void         use() const;
    unsigned int id() const;

private:
    unsigned int        _id;
    std::vector<shader> _attached_shaders;
};