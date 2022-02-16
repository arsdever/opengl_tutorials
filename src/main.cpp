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

#include <entity_manager.h>
#include <triangle.h>
#include <quad.h>
#include <plane.h>
#include <camera.h>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

std::list<camera*> cameras;

void renderScene()
{
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

    entity_manager::instance().add_entity(x);
    entity_manager::instance().add_entity(y);
    entity_manager::instance().add_entity(z);

    x->_color = color{1, 0, 0, 1};
    y->_color = color{0, 1, 0, 1};
    z->_color = color{0, 0, 1, 1};
    x->update_color();
    y->update_color();
    z->update_color();

    static_cast<geometry<vertex> *>(y)->rotate(glm::vec3{0, 3.1415 / 2, 0});
    static_cast<geometry<vertex> *>(z)->rotate(glm::vec3{3.1415 / 2, 0, 0});

    auto entities = entity_manager::instance().entities();
    std::for_each(entities.begin(), entities.end(), [](auto entity)
                  { entity->start(); });
    
    camera* main = new camera();
    cameras.push_back(main);
    main->transformation().move(glm::vec3(0, 0, -3));
    main->set_viewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        std::for_each(cameras.begin(), cameras.end(), [](auto camera) {
            camera->render();
            });

        main->transformation().move(glm::vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::for_each(entities.begin(), entities.end(), [](auto e)
                  { delete e; e = 0; });

    entities.clear();

    return 0;
}