#ifndef GEOMETRY_2D_HPP
#define GEOMETRY_2D_HPP

#include <cmath>
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

    bool is_valid() const { return !((x_ != x_) || (y_ != y_)); }

    Point operator+ (const Point& p) const;
    Point operator- (const Point& p) const;
    bool  operator==(const Point& p) const;
    bool  operator!=(const Point& p) const;

    void print(const char* msg) const;
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

    bool is_valid() const { return !((x_ != x_) || (y_ != y_)); }

    Vec2 operator+ (const Vec2& v) const;
    Vec2 operator- (const Vec2& v) const;
    Vec2 operator* (double sqalar) const;
    bool operator==(const Vec2& v) const;
    bool operator!=(const Vec2& v) const;

    double mod() const;
    Vec2 norm() const;
    Vec2 sqalar(double sqalar) const;
    double dot(const Vec2& v) const;
    bool is_collinear(const Vec2& v) const;

    void print(const char* msg) const;
};

class LineSegment
{
    Point p1_;
    Point p2_;

public:
    LineSegment() :  p1_(Point()), p2_(Point()) {}
    LineSegment(Point p1, Point p2) :  p1_(p1), p2_(p2) {}
    LineSegment(Point p) :  p1_(p), p2_(p) {}

    bool is_valid() const { return p1_.is_valid() && p2_.is_valid(); }

    Point get_p1() const { return p1_; }
    Point get_p2() const { return p2_; }
};

class Line
{
    Point   p_  ;
    Vec2    dir_;

public:
    Line() : p_(Point()), dir_(Vec2()) {}
    Line(Point p, Vec2 dir) : p_(p), dir_(dir) {}
    Line(Point p, double angle) : p_(p), dir_(Vec2(cos(angle), sin(angle))) {}

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

    bool intersection(const Triangle& t) const;

    void print(const char* msg) const;
};

}

#endif
