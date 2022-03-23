#include <action_ctx.hpp>
#include <fps_counter.hpp>
#include <fstream>
#include <iostream>
#include <object.hpp>
#include <scene.hpp>
#include <timer.hpp>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <profiler.hpp>

#include <behaviors/rotate_around_center.hpp>
#include <components/camera.hpp>
#include <components/input_system.hpp>
#include <components/light.hpp>
#include <components/mesh.hpp>
#include <components/renderer.hpp>
#include <components/sample_meshes/stl_mesh.hpp>
#include <components/texture2d.hpp>
#include <components/transform.hpp>

static constexpr int WIDTH  = 1024;
static constexpr int HEIGHT = 768;

gl::object_ptr create_camera_object()
{
    auto           scoped_profiler_instance = prof::profiler::profile(__func__);
    gl::object_ptr cam                      = std::make_shared<gl::object>();
    cam->add_component<gl::camera>();
    cam->add_component<gl::transform>();
    return cam;
}

gl::object_ptr create_light_object()
{
    auto           scoped_profiler_instance = prof::profiler::profile(__func__);
    gl::object_ptr l                        = std::make_shared<gl::object>();
    l->add_component<gl::transform>();
    l->add_component<gl::light>();
    l->add_component<gl::rotate_around_center>();
    l->get_component<gl::rotate_around_center>()->set_speed(1.f);
    l->get_component<gl::light>()->set_color({ 1, 1, 1, 1 });
    return l;
}

gl::object_ptr create_input_system_object(GLFWwindow* win)
{
    auto           scoped_profiler_instance = prof::profiler::profile(__func__);
    gl::object_ptr is                       = std::make_shared<gl::object>();
    is->add_component<gl::input_system>();
    is->get_component<gl::input_system>()->set_window(win);
    return is;
}

gl::object_ptr create_triangle_object()
{
    auto           scoped_profiler_instance = prof::profiler::profile(__func__);
    gl::object_ptr tri                      = std::make_shared<gl::object>();
    gl::texture2d  texture                  = gl::texture2d::from_file("./texture.jpg");
    tri->add_component<gl::transform>();
    tri->add_component<gl::stl_mesh>();
    tri->add_component<gl::renderer>();
    tri->get_component<gl::renderer>()->set_main_texture(texture);
    tri->get_component<gl::stl_mesh>()->load("./axe.stl");
    return tri;
}

GLFWwindow* init_gl_screen()
{
    auto scoped_profiler_instance = prof::profiler::profile(__func__);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
        {
            std::cerr << "Window was not created" << std::endl;
            return 0;
        }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize OpenGL context" << std::endl;
            return 0;
        }

    return window;
}

int main(int argc, char** argv)
{
    {
        auto        scoped_profiler_instance = prof::profiler::profile("main");
        GLFWwindow* window                   = init_gl_screen();
        if (window == 0)
            {
                return -1;
            }

        gl::scene_ptr s = std::make_shared<gl::scene>();
        s->load();

        auto cam   = create_camera_object();
        auto tri   = create_triangle_object();
        auto input = create_input_system_object(window);
        auto light = create_light_object();

        s->add_object(cam);
        s->add_object(tri);
        s->add_object(input);
        s->add_object(light);

        gl::camera_ptr main_camera = cam->get_component<gl::camera>();
        main_camera->set_viewport(gl::camera::rect { 0, 0, WIDTH, HEIGHT });
        main_camera->set_main();
        main_camera->get_component<gl::transform>()->move(glm::vec3 { 0, 0, 3 });

        bool      is_panning = false;
        glm::vec2 position;
        glm::quat rotation;

        input->get_component<gl::input_system>()->on_action(
            "mouse:position", [ &position, &rotation, &is_panning, main_camera ](const gl::action_ctx& ctx) {
                if (!is_panning)
                    return;
                glm::vec2 delta = ctx.value<glm::vec2>() - position;
                main_camera->get_component<gl::transform>()->set_rotation(rotation);
                main_camera->get_component<gl::transform>()->rotate(
                    glm::quat(glm::vec3 { -delta.y / 1000.0, -delta.x / 1000.0, 0 }));
            });
        input->get_component<gl::input_system>()->on_action(
            "mouse:left_click", [ &position, &rotation, main_camera, &is_panning ](const gl::action_ctx& ctx) {
                is_panning = true;
                rotation   = main_camera->get_component<gl::transform>()->rotation();
                position   = ctx.value<glm::vec2>();
            });
        input->get_component<gl::input_system>()->on_action(
            "mouse:left_release",
            [ &position, &rotation, main_camera, &is_panning ](const gl::action_ctx& ctx) { is_panning = false; });
        input->get_component<gl::input_system>()->on_action("keyboard:w", [ main_camera ](const gl::action_ctx& ctx) {
            gl::transform_ptr      tcam  = main_camera->get_component<gl::transform>();
            static constexpr float speed = 40;
            tcam->move(tcam->forward() * gl::timer::delta() * speed);
        });
        input->get_component<gl::input_system>()->on_action("keyboard:s", [ main_camera ](const gl::action_ctx& ctx) {
            gl::transform_ptr      tcam  = main_camera->get_component<gl::transform>();
            static constexpr float speed = 40;
            tcam->move(-tcam->forward() * gl::timer::delta() * speed);
        });
        input->get_component<gl::input_system>()->on_action("keyboard:a", [ main_camera ](const gl::action_ctx& ctx) {
            gl::transform_ptr      tcam  = main_camera->get_component<gl::transform>();
            static constexpr float speed = 20;
            tcam->move(-tcam->right() * gl::timer::delta() * speed);
        });
        input->get_component<gl::input_system>()->on_action("keyboard:d", [ main_camera ](const gl::action_ctx& ctx) {
            gl::transform_ptr      tcam  = main_camera->get_component<gl::transform>();
            static constexpr float speed = 20;
            tcam->move(tcam->right() * gl::timer::delta() * speed);
        });

        gl::fps_counter fps;

        for (auto obj : *gl::scene::current_scene())
            {
                obj->start();
            }

        gl::timer::update();

        fps.start();
        fps.on_data_update([](double data) {
            auto scoped_profiler_instance = prof::profiler::profile("fps_data_update");
            std::cout << "Execution speed: " << data << " fps" << std::endl;
        });
        while (!glfwWindowShouldClose(window))
            {
                {
                    auto scoped_profiler_instance = prof::profiler::profile("main_loop::update_objects");
                    for (auto obj : *gl::scene::current_scene())
                        obj->update();
                }

                {
                    auto scoped_profiler_instance = prof::profiler::profile("main_loop::finish_frame");
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                    gl::timer::update();
                    fps.frame();
                }
            }
    }

    std::ofstream o { "profile.dmp" };
    prof::profiler::save(o);
    o << std::flush;

    return 0;
}