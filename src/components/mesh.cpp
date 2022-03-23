#include <profiler.hpp>

#include "mesh.hpp"

namespace gl
{
    mesh::mesh() { }

    std::vector<vertex>& mesh::vertices() { return _vertices; }

    std::vector<unsigned int>& mesh::indices() { return _indices; }

    const std::vector<vertex>& mesh::vertices() const { return _vertices; }

    const std::vector<unsigned int>& mesh::indices() const { return _indices; }

    bool mesh::is_dirty() const { return _is_dirty; }

    void mesh::upload_data() const
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "mesh::" } + object().lock()->id() + "::" + __func__);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices().size() * sizeof(vertex),
                     static_cast<const void*>(vertices().data()),
                     GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices().size() * sizeof(unsigned long),
                     static_cast<const void*>(indices().data()),
                     GL_STATIC_DRAW);
        _is_dirty = false;
    }
} // namespace gl