#pragma once

#include <geometry.h>
#include <list>

class quad : public geometry
{
public:
    quad();

    virtual const std::list<vertex>& vertices() const override;
    virtual const std::list<unsigned long>& indices() const override;
    virtual unsigned long vertex_count() const override;

private:
    virtual void init() override;

private:
    std::list<vertex> _vertices;
    std::list<unsigned long> _indices;
};