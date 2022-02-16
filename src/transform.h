#pragma once

#include <glm/gtc/type_ptr.hpp>

class transform
{
public:
	transform();

	void set_position(glm::vec3 position);
	void set_rotation(glm::quat rotation);
	void set_scale(glm::vec3 scale);

	void move(glm::vec3 position);
	void rotate(glm::quat rotation);
	void resize(glm::vec3 scale);

	glm::mat4 get_matrix() const;

private:
	glm::mat4 _matrix;
};