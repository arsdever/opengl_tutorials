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
    virtual const std::vector<unsigned int> &indices() const = 0;
    virtual unsigned long vertex_count() const = 0;
    virtual void draw() const;
    virtual void start() override;

protected:
    virtual void init();

    virtual std::vector<vertex_t> &vertices() = 0;
    virtual std::vector<unsigned int> &indices() = 0;

    void draw(unsigned long drawing_mode) const;

private:
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;
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
void geometry<vertex_t>::draw(unsigned long drawing_mode) const
{
    glBindVertexArray(_vao);

    glDrawElements(drawing_mode, indices().size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}