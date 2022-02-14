#pragma once

#include <vertex.h>
#include <list>

class geometry
{
public:
    virtual ~geometry() = default;
    virtual const std::list<vertex>& vertices() const = 0;
    virtual const std::list<unsigned long>& indices() const = 0;
    virtual unsigned long vertex_count() const = 0;

protected:
    virtual void init() = 0;
};