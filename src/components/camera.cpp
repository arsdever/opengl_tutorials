#include "camera.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <scene.hpp>
#include <object.hpp>
#include <components/renderer.hpp>
#include <components/transform.hpp>

namespace gl
{
	camera::camera()
		: _viewport(0, 0, 0, 0)
	{}

	void camera::set_viewport(rect viewport)
	{
		_viewport = viewport;
	}

	void camera::update()
	{
		render();
	}

	glm::mat4 camera::get_perspective() const
	{
		return glm::perspective<double>(
			120.0, _viewport.w / _viewport.h,
			0.001f, 300.0);
	}

	glm::mat4 camera::get_matrix() const
	{
		std::shared_ptr<transform> t = get_component<transform>();

		return get_perspective() * glm::lookAt(t->position(), glm::vec3{ 0, 0, 1 } *t->rotation(), glm::vec3{ 0, 1, 0 });
	}

	void camera::render()
	{
		glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(get_perspective()));

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		for (auto obj : *scene::current_scene())
		{
			std::shared_ptr<renderer> r = obj->get_component<renderer>();
			if (!r)
				continue;

			r->render(std::static_pointer_cast<camera>(shared_from_this()));
		}
	}
}