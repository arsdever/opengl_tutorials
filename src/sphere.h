#pragma once

#include <geometry.h>

class sphere : public geometry
{
public:
    sphere(unsigned segments, unsigned resolution);

    virtual const std::list<vertex>& vertices() const override;
    virtual const std::list<unsigned long>& indices() const override;

private:
    void init();

private:
    unsigned _segments;
    unsigned _resolution;
    std::list<vertex> _vertices;
    std::list<unsigned long> _indices;
};