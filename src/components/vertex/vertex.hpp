#pragma once

#include <array>

#include <glad/glad.h>

#include <components/vertex/color.hpp>
#include <components/vertex/position.hpp>
#include <components/vertex/uv_coords.hpp>

using namespace gl::vertex_attributes;

namespace gl
{
	struct vertex
	{
		vertex(position pos, color col, uv_coords uv)
			: _position{ pos }
			, _color{ col }
			, _uv_coords{ uv }
		{}

		position _position;
		color _color;
		uv_coords _uv_coords;

		static void populate_attributes()
		{
			static int offset = 0;
			static int idx = 0;

			std::array<descriptor_t, 3> dsc{
				position::_descriptor,
				color::_descriptor,
				uv_coords::_descriptor,
			};

			unsigned tsize = 0;
			for (auto d : dsc)
			{
				tsize += std::get<descriptor::size>(d);
			}

			for (auto d : dsc)
			{
				int count = std::get<descriptor::count>(d);
				int type = std::get<descriptor::gltype>(d);
				int norm = std::get<descriptor::glnorm>(d);
				int size = std::get<descriptor::size>(d);
				glVertexAttribPointer(idx++, count, type, norm, tsize, reinterpret_cast<void*>(offset));
				offset += size;
			}

			while (idx)
				glEnableVertexAttribArray(--idx);
		}
	};
}