#pragma once

#include <array>
#include <profiler.hpp>

#include <components/vertex/color.hpp>
#include <components/vertex/normal.hpp>
#include <components/vertex/position.hpp>
#include <components/vertex/uv_coords.hpp>
#include <glad/glad.h>

using namespace gl::vertex_attributes;

namespace gl
{
    struct vertex
    {
        vertex(position pos, color col, uv_coords uv, normal norm)
            : _position { pos }
            , _color { col }
            , _uv_coords { uv }
            , _normal { norm }
        {
        }

        position  _position;
        color     _color;
        uv_coords _uv_coords;
        normal    _normal;

        static void populate_attributes()
        {
            auto       scoped_profiler_instance = prof::profiler::profile(__func__);
            static int offset                   = 0;
            static int idx                      = 0;

            std::array<descriptor_t, 4> dsc {
                position::_descriptor,
                color::_descriptor,
                uv_coords::_descriptor,
                normal::_descriptor,
            };

            unsigned tsize = 0;
            for (auto d : dsc)
                {
                    tsize += std::get<descriptor::size>(d);
                }

            for (auto d : dsc)
                {
                    int count = std::get<descriptor::count>(d);
                    int type  = std::get<descriptor::gltype>(d);
                    int norm  = std::get<descriptor::glnorm>(d);
                    int size  = std::get<descriptor::size>(d);
                    glVertexAttribPointer(idx++, count, type, norm, tsize, reinterpret_cast<void*>(offset));
                    offset += size;
                }

            while (idx)
                glEnableVertexAttribArray(--idx);
        }
    };
} // namespace gl