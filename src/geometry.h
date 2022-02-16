#pragma once

#include <GLES/gl.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <vertex.h>
#include <entity.h>
#include <shader_prog.h>

template <typename V = vertex>
class geometry : public entity
{
public:
    using vertex_t = V;

public:
    geometry();
    virtual ~geometry() = default;
    virtual const std::vector<vertex_t> &vertices() const = 0;
    virtual const std::vector<unsigned int> &indices() const = 0;
    virtual unsigned long vertex_count() const = 0;
    virtual void draw() const;
    virtual void draw(const glm::mat4 &camera) const;
    virtual void start() override;

    void translate(const glm::vec3 &t);
    void rotate(const glm::vec3 &r);
    void scale(const glm::vec3 &s);

protected:
    virtual void init();

    virtual std::vector<vertex_t> &vertices() = 0;
    virtual std::vector<unsigned int> &indices() = 0;

    void draw(unsigned long drawing_mode) const;

private:
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;

    glm::vec3 _translation{0};
    glm::vec3 _rotation{0};
    glm::vec3 _scale{1};

    shader_prog _shader_prog;
    mutable glm::mat4 _camera;
};

template <typename vertex_t>
geometry<vertex_t>::geometry()
{
}

template <typename vertex_t>
void geometry<vertex_t>::init()
{
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glGenVertexArrays(1, &_vao);

    _shader_prog.load_shader("src/shader/vertex.vert");
    _shader_prog.load_shader("src/shader/fragment.frag");
    _shader_prog.link();
}

template <typename vertex_t>
void geometry<vertex_t>::start()
{
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(vertex_t), static_cast<void *>(vertices().data()), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices().size() * sizeof(unsigned long), static_cast<void *>(indices().data()), GL_STATIC_DRAW);

    vertex_t::populate_attributes();
}

template <typename vertex_t>
void geometry<vertex_t>::draw() const
{
    draw(GL_TRIANGLES);
}

template <typename vertex_t>
void geometry<vertex_t>::draw(const glm::mat4 &camera) const
{
    _camera = camera;
    draw(GL_TRIANGLE_STRIP);
}

template <typename vertex_t>
void geometry<vertex_t>::draw(unsigned long drawing_mode) const
{
    glBindVertexArray(_vao);
    _shader_prog.use();

    glDrawElements(drawing_mode, indices().size(), GL_UNSIGNED_INT, 0);

    glm::mat4 transform = glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z);
    transform = glm::translate(transform, _translation);

    unsigned int transformLoc = glGetUniformLocation(_shader_prog.id(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    unsigned int camera = glGetUniformLocation(_shader_prog.id(), "camera");
    glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(_camera));

    glBindVertexArray(0);
}

template <typename vertex_t>
void geometry<vertex_t>::translate(const glm::vec3 &t)
{
    _translation += t;
}

template <typename vertex_t>
void geometry<vertex_t>::rotate(const glm::vec3 &r)
{
    _rotation += r;
}

template <typename vertex_t>
void geometry<vertex_t>::scale(const glm::vec3 &s)
{
    _scale += s;
}