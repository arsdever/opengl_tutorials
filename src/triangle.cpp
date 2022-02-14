#include <triangle.h>

triangle::triangle()
{
    init();
}

const std::list<vertex> &triangle::vertices() const
{
    return _vertices;
}

const std::list<unsigned long> &triangle::indices() const
{
    return _indices;
}

unsigned long triangle::vertex_count() const
{
    return 3;
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
}