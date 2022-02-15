#include "quad.h"

quad::quad()
{
    init();
}

quad::quad(double x, double y, double w, double h)
    : quad()
{
    _vertices[0].x = x;
    _vertices[0].y = y;
    _vertices[1].x = x + w;
    _vertices[1].y = y;
    _vertices[2].x = x;
    _vertices[2].y = y + h;
    _vertices[3].x = x + w;
    _vertices[3].y = y + h;
}

void quad::init()
{
    _vertices.push_back(vertex{-.5, -.5, 0, 1, 0, 0, 1});
    _vertices.push_back(vertex{.5, -.5, 0, 0, 1, 0, 1});
    _vertices.push_back(vertex{-.5, .5, 0, 0, 0, 1, 1});
    _vertices.push_back(vertex{.5, .5, 0, 1, 1, 0, 1});
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);
    _indices.push_back(3);
    geometry::init();
}

const std::vector<vertex> &quad::vertices() const
{
    return _vertices;
}

const std::vector<unsigned int> &quad::indices() const
{
    return _indices;
}

std::vector<vertex> &quad::vertices()
{
    return _vertices;
}

std::vector<unsigned int> &quad::indices()
{
    return _indices;
}

unsigned long quad::vertex_count() const
{
    return 4;
}

void quad::draw() const
{
    geometry::draw(GL_TRIANGLE_STRIP);
}