#pragma once

#include <transform.h>

class camera
{
public:
	struct rect {
		double x;
		double y;
		double w;
		double h;
	};

	camera();

	const transform& transformation() const;
	transform& transformation();
	
	const glm::vec3& target_position() const;
	glm::vec3& target_position();

	void set_viewport(double x, double y, double w, double h);

	void render() const;

private:
	transform _transformation;
	glm::vec3 _target_position;
	rect _viewport;
};