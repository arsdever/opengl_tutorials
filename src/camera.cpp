#include "camera.h"

#include <algorithm>

#include <entity_manager.h>
#include <geometry.h>

camera::camera()
{

}

const transform& camera::transformation() const
{
	return _transformation;
}

transform& camera::transformation()
{
	return _transformation;
}

const glm::vec3& camera::target_position() const
{
	return _target_position;
}

glm::vec3& camera::target_position()
{
	return _target_position;
}

void camera::render() const
{
	glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 perspective = glm::perspective<double>(
		120.0, _viewport.w / _viewport.h,
		0.001f, 300.0);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(perspective));

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	auto ents = entity_manager::instance().entities();
	std::for_each(ents.cbegin(), ents.cend(), [t = _transformation](const entity* ent) {
		if (const geometry<vertex>* geom = dynamic_cast<const geometry<vertex>*>(ent))
			geom->draw(t.get_matrix());
		});
}

void camera::set_viewport(double x, double y, double w, double h)
{
	_viewport.x = x;
	_viewport.y = y;
	_viewport.w = w;
	_viewport.h = h;
}