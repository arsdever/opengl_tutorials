#pragma once

#include <geometry.h>

class quad : public geometry<vertex>
{
public:
    quad();
    quad(double x, double y, double w, double h);

    virtual const std::vector<vertex>& vertices() const override;
    virtual const std::vector<unsigned long>& indices() const override;
    virtual unsigned long vertex_count() const override;

private:
    virtual void init() override;

protected:
    virtual std::vector<vertex_t> &vertices() override;
    virtual std::vector<unsigned long> &indices() override;

private:
    std::vector<vertex> _vertices;
    std::vector<unsigned long> _indices;
};