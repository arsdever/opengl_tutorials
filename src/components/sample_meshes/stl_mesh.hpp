#pragma once

#include <components/mesh.hpp>

namespace gl
{
    class stl_mesh : public mesh
    {
    public:
        void load(std::filesystem::path const& path);
    };
} // namespace gl