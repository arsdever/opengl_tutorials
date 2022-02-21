#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <scene.hpp>
#include <object.hpp>
#include <timer.hpp>
#include <fps_counter.hpp>
#include <action_ctx.hpp>

#include <components/camera.hpp>
#include <components/input_system.hpp>
#include <components/mesh.hpp>
#include <components/transform.hpp>
#include <components/renderer.hpp>

#include <components/sample_meshes/triangle_mesh.hpp>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

gl::object_ptr create_camera_object()
{
	gl::object_ptr cam = std::make_shared<gl::object>();
	cam->add_component<gl::camera>();
	cam->add_component<gl::transform>();
	return cam;
}

gl::object_ptr create_input_system_object(GLFWwindow* win)
{
	gl::object_ptr is = std::make_shared<gl::object>();
	is->add_component<gl::input_system>();
	is->get_component<gl::input_system>()->set_window(win);
	return is;
}

gl::object_ptr create_triangle_object()
{
	gl::object_ptr tri = std::make_shared<gl::object>();
	tri->add_component<gl::transform>();
	tri->add_component<gl::triangle_mesh>();
	tri->add_component<gl::renderer>();
	return tri;
}

GLFWwindow* init_gl_screen()
{
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
	GLFWwindow* window = init_gl_screen();
	if (window == 0)
	{
		return -1;
	}

	gl::scene_ptr s = std::make_shared<gl::scene>();
	s->load();

	auto cam = create_camera_object();
	auto tri = create_triangle_object();
	auto input = create_input_system_object(window);

	s->add_object(cam);
	s->add_object(tri);
	s->add_object(input);

	gl::camera_ptr main_camera = cam->get_component<gl::camera>();
	main_camera->set_viewport(gl::camera::rect{ 0, 0, WIDTH, HEIGHT });
	main_camera->set_main();
	main_camera->get_component<gl::transform>()->move(glm::vec3{ 0, 0, 3 });

	input->get_component<gl::input_system>()->on_action("mouse:position", [main_camera](const gl::action_ctx& ctx) {
		glm::vec2 pos = ctx.value<glm::vec2>();
		main_camera->get_component<gl::transform>()->set_rotation(glm::quat(glm::vec3{ -pos.y / 1000.0, -pos.x / 1000.0, 0 }));
		});
	input->get_component<gl::input_system>()->on_action("mouse:left_click", [main_camera](const gl::action_ctx& ctx) {
		glm::vec2 pos = ctx.value<glm::vec2>();
		gl::transform_ptr tcam = main_camera->get_component<gl::transform>();
		static constexpr float speed = 100;
		tcam->move(tcam->forward() * gl::timer::delta() * speed);
		});
	input->get_component<gl::input_system>()->on_action("mouse:right_click", [main_camera](const gl::action_ctx& ctx) {
		glm::vec2 pos = ctx.value<glm::vec2>();
		gl::transform_ptr tcam = main_camera->get_component<gl::transform>();
		static constexpr float speed = 100;
		tcam->move(-tcam->forward() * gl::timer::delta() * speed);
		});

	gl::fps_counter fps;

	for (auto obj : *gl::scene::current_scene())
	{
		obj->start();
	}

	gl::timer::update();

	fps.start();
	fps.on_data_update([](double data) {std::cout << "Execution speed: " << data << " fps" << std::endl; });
	while (!glfwWindowShouldClose(window))
	{
		for (auto obj : *gl::scene::current_scene())
			obj->update();

		glfwSwapBuffers(window);
		glfwPollEvents();
		gl::timer::update();
		fps.frame();
	}

	return 0;
}