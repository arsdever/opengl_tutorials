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
};