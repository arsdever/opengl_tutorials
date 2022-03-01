#include <iostream>

#include "shader.h"

#include "helper.h"
#include <glad/glad.h>

shader shader::from_file(const std::filesystem::path& path)
{
    shader s;

    std::string ext = path.extension().string();
    if (ext == ".vert")
        s._type = GL_VERTEX_SHADER;
    else if (ext == ".frag")
        s._type = GL_FRAGMENT_SHADER;
    else
        s._type = GL_COMPUTE_SHADER;

    s._id                   = glCreateShader(s._type);
    std::string shader_prog = utils::load_shader_from_file(path.string());
    const char* cstr        = shader_prog.c_str();
    glShaderSource(s._id, 1, &cstr, NULL);
    glCompileShader(s._id);

    int  success;
    char infoLog[ 512 ];
    glGetShaderiv(s._id, GL_COMPILE_STATUS, &success);

    if (!success)
        {
            glGetShaderInfoLog(s._id, 512, NULL, infoLog);
            std::cout << "Failed to compile the shader (" << path << "):\n" << infoLog << std::endl;
        }
    return s;
}

unsigned int shader::id() const { return _id; }