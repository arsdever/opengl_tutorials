#include <glm/glm.hpp>
#include <GLES/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glut/glut.h>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <vector>
#include <list>

#include <helper.h>

#include <entity.h>
#include <triangle.h>
#include <quad.h>
#include <plane.h>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

std::list<entity *> entities;

void renderScene()
{
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    // entities.push_back(new triangle());//-.5, -.5, .5, .7
    // entities.push_back(new quad(0, 0, 1, 1));
    plane *x = new plane();
    plane *y = new plane();
    plane *z = new plane();

    entities.push_back(x);
    entities.push_back(y);
    entities.push_back(z);

    x->_color = color{1, 0, 0, 1};
    y->_color = color{0, 1, 0, 1};
    z->_color = color{0, 0, 1, 1};
    x->update_color();
    y->update_color();
    z->update_color();

    static_cast<geometry<vertex> *>(y)->rotate(glm::vec3{0, 3.1415 / 2, 0});
    static_cast<geometry<vertex> *>(z)->rotate(glm::vec3{3.1415 / 2, 0, 0});

    std::for_each(entities.begin(), entities.end(), [](auto entity)
                  { entity->start(); });

    glm::mat4 perspective = glm::perspective<double>(
        10.0, static_cast<double>(WIDTH) / static_cast<double>(HEIGHT),
        0.001f, 300.0);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(perspective));

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        renderScene();

        std::for_each(entities.begin(), entities.end(), [perspective](auto entity)
                      {
            geometry<vertex>* geom = dynamic_cast<geometry<vertex>*>(entity);
            if (geom)
            {
                // geom->draw();
                glm::mat4 cameraTransform = perspective *
                    glm::lookAt(
                        -glm::vec3{
                            1,
                            1,
                            -2},
                        glm::vec3{0},
                        glm::vec3{0, 1, 0});
                geom->draw(cameraTransform);
            } });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::for_each(entities.begin(), entities.end(), [](auto e)
                  { delete e; e = 0; });

    entities.clear();

    return 0;
}