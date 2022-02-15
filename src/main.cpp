#include <glm/glm.hpp>
#include <GLES/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glut/glut.h>

#include <iostream>
#include <vector>
#include <list>

#include <helper.h>

#include <entity.h>
#include <triangle.h>
#include <quad.h>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

std::list<entity *> entities;

void renderScene()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

auto loadVertexShader()
{
    auto shader = glCreateShader(GL_VERTEX_SHADER);
    std::string shaderProg = utils::load_shader_from_file("src/shader/vertex.vert");
    const char *cstr = shaderProg.c_str();
    glShaderSource(shader, 1, &cstr, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    return shader;
}

auto loadFragmentShader()
{
    auto shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string shaderProg = utils::load_shader_from_file("src/shader/fragment.frag");
    const char *cstr = shaderProg.c_str();
    glShaderSource(shader, 1, &cstr, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    return shader;
}

int main(int argc, char **argv)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cerr << "Window was not created" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    auto vertexShader = loadVertexShader();
    auto fragmentShader = loadFragmentShader();

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM\n"
                  << infoLog << std::endl;
    }

    entities.push_back(new triangle(-.5, -.5, .5, .7));
    entities.push_back(new quad(0, 0, 1, 1));

    std::for_each(entities.begin(), entities.end(), [](auto entity)
                  { entity->start(); });

    glViewport(0, 0, WIDTH, HEIGHT);
    while (!glfwWindowShouldClose(window))
    {
        renderScene();

        std::for_each(entities.begin(), entities.end(), [shaderProgram](auto entity)
                      {
            glUseProgram(shaderProgram);
            geometry<vertex>* geom = dynamic_cast<geometry<vertex>*>(entity);
            if (geom)
            {
                geom->draw();
            } });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}