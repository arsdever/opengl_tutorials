#include <profiler.hpp>

#include "triangle_mesh.hpp"

namespace gl
{
    using namespace vertex_attributes;

    triangle_mesh::triangle_mesh()
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "triangle_mesh::" } + object().lock()->id() + "::" + __func__);
        _vertices.reserve(3);
        _vertices.push_back(
            vertex { position { 0, 0, 0 }, color { 1, 0, 0, 1 }, uv_coords { 0, 0 }, normal { 0, 0, 0 } });
        _vertices.push_back(
            vertex { position { 1, 0, 0 }, color { 0, 1, 0, 1 }, uv_coords { 1, 0 }, normal { 0, 0, 0 } });
        _vertices.push_back(
            vertex { position { 0, 1, 0 }, color { 0, 0, 1, 1 }, uv_coords { 0, 1 }, normal { 0, 0, 0 } });

        _indices.reserve(3);
        _indices.push_back(0);
        _indices.push_back(1);
        _indices.push_back(2);
    }
} // namespace gl