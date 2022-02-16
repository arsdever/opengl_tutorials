#pragma once

#include <geometry.h>

class plane : public geometry<vertex>
{
public:
    plane();
    virtual const std::vector<vertex_t> &vertices() const override;
    virtual const std::vector<unsigned int> &indices() const override;
    virtual unsigned long vertex_count() const override;
    virtual void draw() const override;

protected:
    virtual void init() override;

    virtual std::vector<vertex_t> &vertices() override;
    virtual std::vector<unsigned int> &indices() override;

private:
    std::vector<vertex_t> _vertices;
    std::vector<unsigned int> _indices;

public:
    color _color;
    void update_color();
};