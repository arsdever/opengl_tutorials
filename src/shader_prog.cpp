#include "shader_prog.h"

#include <glad/glad.h>

#include <iostream>

shader_prog::shader_prog()
{
    _id = glCreateProgram();
}

void shader_prog::load_shader(const std::filesystem::path &path)
{
    shader s = shader::from_file(path);
    glAttachShader(_id, s.id());
    _attached_shaders.push_back(std::move(s));
}

void shader_prog::link()
{
    std::for_each(_attached_shaders.begin(), _attached_shaders.end(), [id = this->_id](auto shader)
                  { glAttachShader(id, shader.id()); });
    glLinkProgram(_id);
    int success;
    char infoLog[512];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "Error linking shader program:\n"
                  << infoLog << std::endl;
    }

    std::for_each(_attached_shaders.begin(), _attached_shaders.end(), [](auto shader)
                  { glDeleteShader(shader.id()); });
}

void shader_prog::use() const
{
    glUseProgram(_id);
}

unsigned int shader_prog::id() const
{
    return _id;
}