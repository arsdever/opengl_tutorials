#include <glm/glm.hpp>
#include <GLES/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glut/glut.h>

#include <iostream>
#include <vector>

#include <helper.h>

#include <triangle.h>
#include <quad.h>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

static const quad t;

#define SHADER(prog) #prog

void renderScene()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

auto loadVertexShader()
{
    auto shader = glCreateShader(GL_VERTEX_SHADER);
    std::string shaderProg = utils::load_shader_from_file("src/shader/vertex.vert");
    const char* cstr = shaderProg.c_str();
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
    const char* cstr = shaderProg.c_str();
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

    std::vector<double> buffer;
    std::for_each(t.vertices().begin(), t.vertices().end(), [&buffer](auto vertex)
                  {
                    buffer.push_back(vertex.x);
                    buffer.push_back(vertex.y);
                    buffer.push_back(vertex.z); });

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(double), buffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void *)0);
    glEnableVertexAttribArray(0);

    glViewport(0, 0, WIDTH, HEIGHT);
    while (!glfwWindowShouldClose(window))
    {
        renderScene();

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, t.indices().size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}