#pragma once

#include "descriptor.hpp"
#include <glad/glad.h>

namespace gl::vertex_attributes
{
    struct color
    {
        color(float _r, float _g, float _b, float _a = 1.0f)
            : r(_r)
            , g(_g)
            , b(_b)
            , a(_a)
        {
        }

        color(const color& _o)
            : r(_o.r)
            , g(_o.g)
            , b(_o.b)
            , a(_o.a)
        {
        }

        float r;
        float g;
        float b;
        float a;

        inline static descriptor_t _descriptor =
            std::make_tuple<unsigned, int, bool, unsigned>(4, GL_FLOAT, GL_FALSE, 4 * sizeof(float));
    };
} // namespace gl::vertex_attributes