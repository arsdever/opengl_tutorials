#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <scene.hpp>
#include <object.hpp>
#include <timer.hpp>
#include <fps_counter.hpp>

#include <components/camera.hpp>
#include <components/transform.hpp>
#include <components/sample_meshes/triangle_mesh.hpp>
#include <components/mesh.hpp>
#include <components/renderer.hpp>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;
static std::shared_ptr<gl::camera> main_camera = nullptr;

gl::object_ptr create_camera_object()
{
	gl::object_ptr cam = std::make_shared<gl::object>();
	cam->add_component<gl::camera>();
	cam->add_component<gl::transform>();
	return cam;
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

void mouse_position_cb(GLFWwindow*, double x, double y)
{
	auto t = main_camera->get_component<gl::transform>();
}

void keypress_cb(GLFWwindow* window, int key, int scan, int action, int mode)
{
	auto t = main_camera->get_component<gl::transform>();
	if (key == GLFW_KEY_W)
	{
		t->move(glm::vec3{ 0, 0, -1 } *gl::timer::delta());
	}
	if (key == GLFW_KEY_D)
	{
		t->move(glm::vec3{ 1, 0, 0 } *gl::timer::delta());
	}
	if (key == GLFW_KEY_S)
	{
		t->move(glm::vec3{ 0, 0, 1 } *gl::timer::delta());
	}
	if (key == GLFW_KEY_A)
	{
		t->move(glm::vec3{ -1, 0, 0 } *gl::timer::delta());
	}
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

	s->add_object(cam);
	s->add_object(tri);

	main_camera = cam->get_component<gl::camera>();
	main_camera->set_viewport(gl::camera::rect{ 0, 0, WIDTH, HEIGHT });
	gl::fps_counter fps;

	for (auto obj : *gl::scene::current_scene())
	{
		obj->start();
	}

	glfwSetCursorPosCallback(window, &mouse_position_cb);
	glfwSetKeyCallback(window, &keypress_cb);
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