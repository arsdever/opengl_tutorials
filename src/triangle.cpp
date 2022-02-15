#include <triangle.h>

triangle::triangle()
{
    init();
}

triangle::triangle(double l, double d, double w, double h)
    : triangle()
{
    _vertices[0].x = l;
    _vertices[0].y = d;
    _vertices[1].x = l + w;
    _vertices[1].y = d;
    _vertices[2].x = l + w / 2.0;
    _vertices[2].y = l + h;
}

const std::vector<vertex> &triangle::vertices() const
{
    return _vertices;
}

const std::vector<unsigned int> &triangle::indices() const
{
    return _indices;
}

unsigned long triangle::vertex_count() const
{
    return 3;
}

std::vector<vertex> &triangle::vertices()
{
    return _vertices;
}

std::vector<unsigned int> &triangle::indices()
{
    return _indices;
}

void triangle::init()
{
    if (_initialized)
        return;

    _initialized = true;

    _vertices.push_back(vertex(-.5, -.288, 0, 1, 0, 0, 1));
    _vertices.push_back(vertex(.5, -.288, 0, 0, 1, 0, 1));
    _vertices.push_back(vertex(0, .576, 0, 0, 0, 1, 1));

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);
    geometry::init();
}