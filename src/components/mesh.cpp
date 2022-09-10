#include <profiler.hpp>

#include "mesh.hpp"

namespace gl
{
    mesh::mesh(object_wptr o)
        : component(o)
    {
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);
        glGenVertexArrays(1, &_vao);

        glBindVertexArray(_vao);

        std::shared_ptr<mesh> m = get_component<mesh>();

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        upload_data();

        glBindVertexArray(0);
    }

    std::vector<vertex>& mesh::vertices() { return _vertices; }

    std::vector<unsigned int>& mesh::indices() { return _indices; }

    const std::vector<vertex>& mesh::vertices() const { return _vertices; }

    const std::vector<unsigned int>& mesh::indices() const { return _indices; }

    bool mesh::is_dirty() const { return _is_dirty; }

    void mesh::upload_data() const
    {
        glBindVertexArray(_vao);

        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices().size() * sizeof(vertex),
                     static_cast<const void*>(vertices().data()),
                     GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices().size() * sizeof(unsigned long),
                     static_cast<const void*>(indices().data()),
                     GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    unsigned int mesh::buffer_array() const { return _vao; }
} // namespace gl