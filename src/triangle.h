#pragma once

#include <geometry.h>

class triangle : public geometry<vertex>
{
public:
    triangle();
    triangle(double l, double d, double w, double h);

    virtual const std::vector<vertex_t> &vertices() const override;
    virtual const std::vector<unsigned long> &indices() const override;
    virtual unsigned long vertex_count() const override;

private:
    virtual void init() override;

protected:
    virtual std::vector<vertex_t> &vertices() override;
    virtual std::vector<unsigned long> &indices() override;

private:
    bool _initialized { false };
    std::vector<vertex_t> _vertices;
    std::vector<unsigned long> _indices;
};