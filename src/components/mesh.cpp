#include "mesh.hpp"

namespace gl
{
    mesh::mesh() { }

    std::vector<vertex>& mesh::vertices() { return _vertices; }

    std::vector<unsigned int>& mesh::indices() { return _indices; }

    const std::vector<vertex>& mesh::vertices() const { return _vertices; }

    const std::vector<unsigned int>& mesh::indices() const { return _indices; }
} // namespace gl