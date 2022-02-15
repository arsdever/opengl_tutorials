#pragma once

#include <geometry.h>

class quad : public geometry<vertex>
{
public:
    quad();
    quad(double x, double y, double w, double h);

    virtual const std::vector<vertex> &vertices() const override;
    virtual const std::vector<unsigned int> &indices() const override;
    virtual unsigned long vertex_count() const override;
    virtual void draw() const override;

private:
    virtual void init() override;

protected:
    virtual std::vector<vertex_t> &vertices() override;
    virtual std::vector<unsigned int> &indices() override;

private:
    std::vector<vertex> _vertices;
    std::vector<unsigned int> _indices;
};