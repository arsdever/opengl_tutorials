#pragma once

#include "descriptor.hpp"

#include <glad/glad.h>

namespace gl::vertex_attributes
{
	struct uv_coords
	{
		uv_coords(float _x, float _y) : x(_x), y(_y) { }

		uv_coords(const uv_coords& _o) : x(_o.x), y(_o.y) { }

		float x;
		float y;

		inline static descriptor_t _descriptor =
			std::make_tuple<unsigned, int, bool, unsigned>(2, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	};
} // namespace gl::vertex_attributes