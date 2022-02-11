#pragma once

#include <geometry.h>

class triangle : public geometry
{
public:
    triangle();

    virtual const std::list<vertex> &vertices() const override;
    virtual const std::list<unsigned long> &indices() const override;

private:
    void init();

private:
    bool _initialized { false };
    std::list<vertex> _vertices;
    std::list<unsigned long> _indices;
};