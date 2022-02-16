#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

transform::transform()
	: _matrix{ 0 }
{
	_matrix[0][0] = 1;
	_matrix[1][1] = 1;
	_matrix[2][2] = 1;
}

void transform::set_position(glm::vec3 position)
{

}

void transform::set_rotation(glm::quat rotation)
{

}

void transform::set_scale(glm::vec3 scale)
{
	
}

void transform::move(glm::vec3 position)
{
	glm::translate(_matrix, position);
}

void transform::rotate(glm::quat rotation)
{
	_matrix * glm::mat4_cast(rotation);
}

void transform::resize(glm::vec3 scale)
{
	glm::scale(_matrix, scale);
}

glm::mat4 transform::get_matrix() const
{
	return _matrix;
}