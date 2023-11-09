#ifndef GEOMETRY_2D_CPP
#define GEOMETRY_2D_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#include "../Include/Geometry2D.hpp"

using namespace Geometry2D;


Point Point::operator+ (const Point& p) const { return Point(x_+p.x_, y_+p.y_)                    ; }
Point Point::operator- (const Point& p) const { return Point(x_-p.x_, y_-p.y_)                    ; }
bool  Point::operator==(const Point& p) const { return fabs(x_-p.x_) < EPS && fabs(y_-p.y_) < EPS ; }
bool  Point::operator!=(const Point& p) const { return !(*this == p)                              ; }

void Point::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ")";
}


Vec2 Vec2::operator+ (const Vec2& v) const { return Vec2(x_+v.x_, y_+v.y_)                     ; }
Vec2 Vec2::operator- (const Vec2& v) const { return Vec2(x_-v.x_, y_-v.y_)                     ; }
Vec2 Vec2::operator* (double sqalar) const { return Vec2(x_*sqalar, y_*sqalar)                 ; }
bool Vec2::operator==(const Vec2& v) const { return fabs(x_-v.x_) < EPS && fabs(y_-v.y_) < EPS ; }
bool Vec2::operator!=(const Vec2& v) const { return !(*this == v)                              ; }

double Vec2::mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2)); }

Vec2 Vec2::norm() const
{
    double mod = this->mod();
    return Vec2(x_/mod, y_/mod);
}

Vec2 Vec2::sqalar(double sqalar) const { return Vec2(x_*sqalar, y_*sqalar); }
double Vec2::dot(const Vec2& v) const { return x_*v.x_ + y_*v.y_; }
bool Vec2::is_collinear(const Vec2& v) const { return x_*v.y_ - y_*v.x_ < EPS; }

void Vec2::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ")" << std::endl;
}


bool Triangle::intersection(const Triangle& t) const
{
    //
    return true;
}

void Triangle::print(const char* msg = "") const
{
    std::cout << msg;

    p1_.print();
    p2_.print(" ");
    p3_.print(" ");

    std::cout << std::endl;
}

#endif
