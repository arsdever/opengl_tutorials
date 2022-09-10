#pragma once

#include <components/mesh.hpp>

namespace gl
{
    class stl_mesh : public mesh
    {
    public:
        stl_mesh(object_wptr o);
        void load(std::filesystem::path const& path);
    };
} // namespace gl