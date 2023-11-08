#ifndef GEOMETRY_2D_HPP
#define GEOMETRY_2D_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

namespace Geometry2D
{

const double EPS = std::numeric_limits<float>::epsilon();

struct Point
{
    double x_ = NAN;
    double y_ = NAN;

    Point() : x_(0.0), y_(0.0) {}
    Point(double x, double y) : x_(x), y_(y) {}

    bool is_valid() const
    {
        return !((x_ != x_) || (y_ != y_));
    }

    Point operator+ (const Point& p) const { return Point(x_+p.x_, y_+p.y_)                    ; }
    Point operator- (const Point& p) const { return Point(x_-p.x_, y_-p.y_)                    ; }
    bool  operator==(const Point& p) const { return fabs(x_-p.x_) < EPS && fabs(y_==p.y_) < EPS; }
    bool  operator!=(const Point& p) const { return !(*this == p)                              ; }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ")";
    }
};

class Vec2
{
    double x_ = NAN;
    double y_ = NAN;

public:
    Vec2() : x_(0.0), y_(0.0) {}
    Vec2(double x, double y) : x_(x), y_(y) {}
    Vec2(Point& p1, Point& p2) : x_(p2.x_-p1.x_), y_(p2.y_-p1.y_) {}
    Vec2(Point& p) : x_(p.x_), y_(p.y_) {}

    double get_x() const { return x_; }
    double get_y() const { return y_; }

    bool is_valid() const
    {
        return !((x_ != x_) || (y_ != y_));
    }

    Vec2 operator+ (const Vec2& v) const { return Vec2(x_+v.x_, y_+v.y_)                     ; }
    Vec2 operator- (const Vec2& v) const { return Vec2(x_-v.x_, y_-v.y_)                     ; }
    Vec2 operator* (double sqalar) const { return Vec2(x_*sqalar, y_*sqalar)                 ; }
    bool operator==(const Vec2& v) const { return fabs(x_-v.x_) < EPS && fabs(y_==v.y_) < EPS; }
    bool operator!=(const Vec2& v) const { return !(*this == v)                              ; }

    double mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2)); }

    Vec2 norm()
    {
        double mod = this->mod();
        return Vec2(x_/mod, y_/mod);
    }

    Vec2 sqalar(double sqalar) const { return Vec2(x_*sqalar, y_*sqalar); }
    double dot(const Vec2& v) const { return x_*v.x_ + y_*v.y_; }
    // double angle(const Vec2& v) const { return acos(dot(v)/(mod()*v.mod())); }
    bool is_collinear(const Vec2& v) const { return x_*v.y_ - y_*v.x_ < EPS; }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ")" << std::endl;
    }
};

class LineSegment
{
    Point p1_;
    Point p2_;

public:
    LineSegment () :  p1_(Point()), p2_(Point()) {}
    LineSegment (Point p1, Point p2) :  p1_(p1), p2_(p2) {}
    LineSegment (Point p) :  p1_(p), p2_(p) {}

    bool is_valid() const { return p1_.is_valid() && p2_.is_valid(); }

    Point get_p1() const { return p1_; }
    Point get_p2() const { return p2_; }
};

class Line
{
    Point   p_  ;
    Vec2    dir_;

public:
    Line () : p_(Point()), dir_(Vec2()) {}
    Line (Point p, Vec2 dir) : p_(p), dir_(dir) {}
    Line (Point p, double angle) : p_(p), dir_(Vec2(cos(angle), sin(angle))) {}

    bool is_valid() const { return p_.is_valid() && dir_.is_valid() && (dir_ != Vec2()); }

    Point get_p()   const { return p_  ; }
    Vec2  get_dir() const { return dir_; }
};

class Triangle
{
    Point p1_;
    Point p2_;
    Point p3_;

public:
    Triangle() : p1_(Point()), p2_(Point()), p3_(Point()) {}
    Triangle(Point p1, Point p2, Point p3) : p1_(p1), p2_(p2), p3_(p3) {}
    Triangle(Point p1, Point p2) : p1_(p1), p2_(p2), p3_(p2) {}
    Triangle(Point p) : p1_(p), p2_(p), p3_(p) {}

    bool is_valid() const { return p1_.is_valid() && p2_.is_valid() && p3_.is_valid(); }

    Point get_p1() const { return p1_; }
    Point get_p2() const { return p2_; }
    Point get_p3() const { return p3_; }

    void print(const char* msg = "") const
    {
        std::cout << msg;

        p1_.print();
        p2_.print(" ");
        p3_.print(" ");

        std::cout << std::endl;
    }
};

}

#endif
