#include <filesystem>
#include <fstream>
#include <profiler.hpp>
#include <stl.hpp>

#include "stl_mesh.hpp"

namespace gl
{
    using namespace vertex_attributes;

    stl_mesh::stl_mesh(object_wptr o)
        : mesh { o }
    {
    }

    void stl_mesh::load(std::filesystem::path const& path)
    {
        auto          scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        std::ifstream reader(path, std::ios::binary);
        std::vector<uint8_t> buffer { std::istreambuf_iterator { reader }, {} };
        gl::stl              stl { buffer.data() };
        uint32_t             index { 0 };

        _vertices.reserve(stl.number_of_triangles() * 3);
        _indices.reserve(stl.number_of_triangles() * 3);

        for (gl::stl::triangle const& t : stl)
            {
                _vertices.push_back(vertex { position { t.v1[ 0 ], t.v1[ 1 ], t.v1[ 2 ] },
                                             color { 1, 0, 0, 1 },
                                             uv_coords { 0, 0 },
                                             normal { t.normal[ 0 ], t.normal[ 1 ], t.normal[ 2 ] } });
                _vertices.push_back(vertex { position { t.v2[ 0 ], t.v2[ 1 ], t.v2[ 2 ] },
                                             color { 1, 0, 0, 1 },
                                             uv_coords { 0, 0 },
                                             normal { t.normal[ 0 ], t.normal[ 1 ], t.normal[ 2 ] } });
                _vertices.push_back(vertex { position { t.v3[ 0 ], t.v3[ 1 ], t.v3[ 2 ] },
                                             color { 1, 0, 0, 1 },
                                             uv_coords { 0, 0 },
                                             normal { t.normal[ 0 ], t.normal[ 1 ], t.normal[ 2 ] } });
                _indices.push_back(index++);
                _indices.push_back(index++);
                _indices.push_back(index++);
            }

        upload_data();
    }
} // namespace gl