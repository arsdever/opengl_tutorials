#include "quad.h"

quad::quad()
{
    init();
}

void quad::init()
{
    _vertices.push_back(vertex{-.5, -.5, 0});
    _vertices.push_back(vertex{.5, -.5, 0});
    _vertices.push_back(vertex{-.5, .5, 0});
    _vertices.push_back(vertex{.5, .5, 0});
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);
    _indices.push_back(3);
}

const std::list<vertex> &quad::vertices() const
{
    return _vertices;
}

const std::list<unsigned long> &quad::indices() const
{
    return _indices;
}

unsigned long quad::vertex_count() const
{
    return 4;
}