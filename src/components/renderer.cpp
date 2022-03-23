#include <profiler.hpp>
#include <scene.hpp>

#include "renderer.hpp"

#include <GLES/gl.h>
#include <components/camera.hpp>
#include <components/light.hpp>
#include <components/mesh.hpp>
#include <components/transform.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace gl
{
    void renderer::start()
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "renderer::" } + object().lock()->id() + "::" + __func__);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);
        glGenVertexArrays(1, &_vao);
        glGenTextures(1, &_texture);

        _shader_prog.load_shader("src/shader/vertex.vert");
        _shader_prog.load_shader("src/shader/fragment.frag");
        _shader_prog.link();

        glBindVertexArray(_vao);

        std::shared_ptr<mesh> m = get_component<mesh>();

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        m->upload_data();

        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     static_cast<int>(_main_texture.width()),
                     static_cast<int>(_main_texture.height()),
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     _main_texture.data().data());
        glGenerateMipmap(GL_TEXTURE_2D);

        vertex::populate_attributes();
    }

    void renderer::render(std::shared_ptr<camera> cam)
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "renderer::" } + object().lock()->id() + "::" + __func__);
        glBindVertexArray(_vao);
        _shader_prog.use();

        std::shared_ptr<mesh>      m = get_component<mesh>();
        std::shared_ptr<transform> t = get_component<transform>();

        if (m->is_dirty())
            m->upload_data();

        unsigned int transformLoc = glGetUniformLocation(_shader_prog.id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(t->get_matrix()));

        unsigned int camera = glGetUniformLocation(_shader_prog.id(), "camera");
        glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cam->get_matrix()));

        for (auto const& obj : *scene::current_scene())
            {
                std::shared_ptr<light> l = obj->get_component<light>();
                if (l)
                    {
                        unsigned int position  = glGetUniformLocation(_shader_prog.id(), "_light[0].position");
                        unsigned int color     = glGetUniformLocation(_shader_prog.id(), "_light[0].color");
                        unsigned int intencity = glGetUniformLocation(_shader_prog.id(), "_light[0].intencity");

                        std::shared_ptr<transform> lt = l->get_component<transform>();
                        glUniform3fv(position, 1, glm::value_ptr(cam->get_component<transform>()->position()));
                        glUniform4fv(color, 1, glm::value_ptr(l->color()));
                        glUniform1f(intencity, l->intencity());
                    }
            }

        glBindTexture(GL_TEXTURE_2D, _texture);

        glDrawElements(GL_TRIANGLES, m->indices().size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    texture2d renderer::main_texture() const { return _main_texture; }

    void renderer::set_main_texture(const texture2d& texture) { _main_texture = texture; }
} // namespace gl