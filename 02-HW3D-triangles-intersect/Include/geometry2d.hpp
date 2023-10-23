#ifndef GEOMETRY2D_HPP
#define GEOMETRY2D_HPP

#include <iostream>

#define FLT_TOLERANCE 0.001f

struct point2d_t
{
    float x = 0, y = 0;

    void print() const { std::cout << "point:\t(" << x << ", " << y << ")\n\n"; }
    bool equal(const point2d_t &other) const { return (std::abs(x - other.x) <  FLT_TOLERANCE) && 
                                                      (std::abs(y - other.y) <  FLT_TOLERANCE); }
};

// line in of form of "ax + by + c = 0"
struct line2d_t
{
    float a = -1.0f, b = 1.0f, c = 0.0f;

    void print() const { std::cout << "line:\t" << a << "x + " << b << "y + " << c << " = 0\n\n"; }
    bool valid() const { return (a != 0) || (b != 0); }
    bool equal(const line2d_t &other) const { return (std::abs(a - other.a) <  FLT_TOLERANCE) &&
                                                     (std::abs(b - other.b) <  FLT_TOLERANCE) &&
                                                     (std::abs(c - other.c) <  FLT_TOLERANCE); }
};

struct line_segment2d_t
{
    point2d_t begin{0.0f, 0.0f}, end{0.0f, 0.0f};

    void print() const { std::cout << "line segmant:\t(" << begin.x << ", " << begin.y << ") ---> (" << 
                                   end.x << ", " << end.y << ")\n\n"; }
    bool valid() const { return !begin.equal(end); }
};

struct triangle2d_t
{
    point2d_t P1{0, 0}, P2{0, 0}, P3{0, 0};

    bool valid() const { return 1; }
};

#endif