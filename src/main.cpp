#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <scene.hpp>
#include <object.hpp>

#include <components/camera.hpp>
#include <components/transform.hpp>
#include <components/sample_meshes/triangle_mesh.hpp>
#include <components/mesh.hpp>
#include <components/renderer.hpp>

static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;

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

	cam->get_component<gl::camera>()->set_viewport(gl::camera::rect{ 0, 0, WIDTH, HEIGHT });

	for (auto obj : *gl::scene::current_scene())
	{
		obj->start();
	}

	while (!glfwWindowShouldClose(window))
	{
		for (auto obj : *gl::scene::current_scene())
			obj->update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}