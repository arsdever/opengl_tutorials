#include "triangle_mesh.hpp"

namespace gl
{
	triangle_mesh::triangle_mesh()
	{
		_vertices.reserve(3);
		_vertices.push_back(vertex{ 0, 0, 0, 1, 0, 0, 1 });
		_vertices.push_back(vertex{ 1, 0, 0, 0, 1, 0, 1 });
		_vertices.push_back(vertex{ 0, 1, 0, 0, 0, 1, 1 });

		_indices.reserve(3);
		_indices.push_back(0);
		_indices.push_back(1);
		_indices.push_back(2);
	}
}