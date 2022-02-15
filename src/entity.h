#pragma once

class entity
{
public:
    virtual ~entity() = default;
    virtual void start() = 0;
};