#include "plane.h"

plane::plane()
{
    init();
}

const std::vector<plane::vertex_t> &plane::vertices() const
{
    return _vertices;
}

const std::vector<unsigned int> &plane::indices() const
{
    return _indices;
}

std::vector<plane::vertex_t> &plane::vertices()
{
    return _vertices;
}

std::vector<unsigned int> &plane::indices()
{
    return _indices;
}

unsigned long plane::vertex_count() const
{
    return 4;
}

void plane::init()
{
    _vertices.push_back(vertex{-.7, -.7, 0});
    _vertices.push_back(vertex{-.7, .7, 0});
    _vertices.push_back(vertex{.7, -.7, 0});
    _vertices.push_back(vertex{.7, .7, 0});
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);
    _indices.push_back(3);
    geometry::init();
}

void plane::update_color()
{
    std::for_each(_vertices.begin(), _vertices.end(), [c = _color](auto &v)
                  { v.c = c; });
}

void plane::draw() const
{
    geometry::draw(GL_TRIANGLE_STRIP);
}