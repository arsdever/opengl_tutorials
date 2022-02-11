#include "sphere.h"

sphere::sphere(unsigned segments, unsigned resolution)
    : _segments(segments)
    , _resolution(resolution)
{}

void sphere::init()
{
    // Calculate vertices
}

const std::list<vertex>& sphere::vertices() const
{
    return _vertices;
}

const std::list<unsigned long>& sphere::indices() const
{
    return _indices;
}