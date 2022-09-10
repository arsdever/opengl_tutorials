#pragma once

#include <components/mesh.hpp>

namespace gl
{
    class triangle_mesh : public mesh
    {
    public:
        triangle_mesh(object_wptr o);
    };
} // namespace gl