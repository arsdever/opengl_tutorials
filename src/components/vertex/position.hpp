#pragma once

#include <glad/glad.h>

#include "descriptor.hpp"

namespace gl::vertex_attributes
{
	struct position
	{
		position(float _x, float _y, float _z)
			: x(_x)
			, y(_y)
			, z(_z)
		{}

		position(const position& _o)
			: x(_o.x)
			, y(_o.y)
			, z(_o.z)
		{}

		float x;
		float y;
		float z;

		inline static descriptor_t _descriptor = std::make_tuple<unsigned, int, bool, unsigned>(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	};
}