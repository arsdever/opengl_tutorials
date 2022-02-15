#pragma once

struct vertex
{
    vertex(double _x, double _y, double _z, double _r = 1, double _g = 0, double _b = 0, double _a = 1) 
        : x(_x)
        , y(_y)
        , z(_z)
        , r(_r)
        , g(_g)
        , b(_b)
        , a(_a) {}
    double x;
    double y;
    double z;
    double r;
    double g;
    double b;
    double a;

    static void populate_attributes()
    {
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void *)0);
        glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void *)(3 * sizeof(double)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
};