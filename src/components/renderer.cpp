#include "renderer.hpp"

#include <GLES/gl.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <components/mesh.hpp>
#include <components/transform.hpp>
#include <components/camera.hpp>

namespace gl
{

	void renderer::start()
	{
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);
		glGenVertexArrays(1, &_vao);

		_shader_prog.load_shader("src/shader/vertex.vert");
		_shader_prog.load_shader("src/shader/fragment.frag");
		_shader_prog.link();

		glBindVertexArray(_vao);

		std::shared_ptr<mesh> m = get_component<mesh>();

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, m->vertices().size() * sizeof(vertex), static_cast<void*>(m->vertices().data()), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indices().size() * sizeof(unsigned long), static_cast<void*>(m->indices().data()), GL_STATIC_DRAW);

		vertex::populate_attributes();
	}

	void renderer::render(std::shared_ptr<camera> cam)
	{
		glBindVertexArray(_vao);
		_shader_prog.use();

		std::shared_ptr<mesh> m = get_component<mesh>();
		std::shared_ptr<transform> t = get_component<transform>();

		glDrawElements(GL_TRIANGLES, m->indices().size(), GL_UNSIGNED_INT, 0);

		unsigned int transformLoc = glGetUniformLocation(_shader_prog.id(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(t->get_matrix()));

		unsigned int camera = glGetUniformLocation(_shader_prog.id(), "camera");
		glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cam->get_matrix()));

		glBindVertexArray(0);
	}
}