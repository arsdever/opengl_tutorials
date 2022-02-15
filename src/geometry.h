#pragma once

#include <glad/glad.h>

#include <vertex.h>
#include <entity.h>
#include <vector>

template <typename V = vertex>
class geometry : public entity
{
public:
    using vertex_t = V;

public:
    geometry();
    virtual ~geometry() = default;
    virtual const std::vector<vertex_t> &vertices() const = 0;
    virtual const std::vector<unsigned long> &indices() const = 0;
    virtual unsigned long vertex_count() const = 0;
    virtual void draw() const;
    virtual void start() override;

protected:
    virtual void init();

    virtual std::vector<vertex_t> &vertices() = 0;
    virtual std::vector<unsigned long> &indices() = 0;

private:
    unsigned int _vbo;
    unsigned int _vao;
};

template <typename vertex_t>
geometry<vertex_t>::geometry()
{
}

template <typename vertex_t>
void geometry<vertex_t>::init()
{
    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

template <typename vertex_t>
void geometry<vertex_t>::start()
{
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    std::vector<vertex_t>& v = vertices();

    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(vertex_t), static_cast<void*>(v.data()), GL_STATIC_DRAW);

    vertex_t::populate_attributes();
}

template <typename vertex_t>
void geometry<vertex_t>::draw() const
{
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, indices().size());
}