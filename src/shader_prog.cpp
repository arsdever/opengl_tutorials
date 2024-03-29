#include <iostream>
#include <profiler.hpp>

#include "shader_prog.h"

#include <glad/glad.h>

shader_prog::shader_prog()
{
    auto scoped_profiler_instance = prof::profiler::profile(__func__);
    _id                           = glCreateProgram();
}

void shader_prog::load_shader(const std::filesystem::path& path)
{
    auto   scoped_profiler_instance = prof::profiler::profile(__func__);
    shader s                        = shader::from_file(path);
    glAttachShader(_id, s.id());
    _attached_shaders.push_back(std::move(s));
}

void shader_prog::link()
{
    auto scoped_profiler_instance = prof::profiler::profile(__func__);
    std::for_each(_attached_shaders.begin(), _attached_shaders.end(), [ id = this->_id ](auto shader) {
        glAttachShader(id, shader.id());
    });
    glLinkProgram(_id);
    int  success;
    char infoLog[ 512 ];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
        {
            glGetProgramInfoLog(_id, 512, NULL, infoLog);
            std::cout << "Error linking shader program:\n" << infoLog << std::endl;
        }

    std::for_each(_attached_shaders.begin(), _attached_shaders.end(), [](auto shader) { glDeleteShader(shader.id()); });
}

void shader_prog::use() const
{
    auto scoped_profiler_instance = prof::profiler::profile(__func__);
    glUseProgram(_id);
}

unsigned int shader_prog::id() const { return _id; }