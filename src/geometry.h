#pragma once

#include <vertex.h>
#include <list>

class geometry
{
public:
    virtual ~geometry() = default;
    virtual const std::list<vertex>& vertices() const = 0;
    virtual const std::list<unsigned long>& indices() const = 0;
};