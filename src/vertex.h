#pragma once

#include <glad/glad.h>

struct color
{
    color() = default;
    color(double _r, double _g, double _b, double _a)
        : r(_r), g(_g), b(_b), a(_a) {}

    color &operator=(const color &o)
    {
        r = o.r;
        g = o.g;
        b = o.b;
        a = o.a;
        return *this;
    }

    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 0.0;
};

struct vertex
{
    vertex(double _x, double _y, double _z, double _r = 1, double _g = 0, double _b = 0, double _a = 1)
        : x(_x), y(_y), z(_z), c(_r, _g, _b, _a) {}
    double x;
    double y;
    double z;
    color c;

    static void populate_attributes()
    {
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void *)0);
        glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void *)(3 * sizeof(double)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
};