#ifndef GEOMETRY_3D_HPP
#define GEOMETRY_3D_HPP

#include <cmath>
#include <vector>
#include <limits>

#include "../Include/Geometry2D.hpp"

namespace Geometry3D {

const double EPS = std::numeric_limits<double>::epsilon();

struct Point
{
    double x_ = NAN;
    double y_ = NAN;
    double z_ = NAN;

    Point() : x_(0.0), y_(0.0), z_(0.0) {}
    Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    bool is_valid() const { return !((x_ != x_) || (y_ != y_) || (z_ != z_)); }

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;

    Geometry2D::Point to_point2D() const;
    // Vec3 to_vec() const { return Vec3(x_, y_, z_); }

    void print(const char* msg) const;
};

class Vec3
{
    double x_ = NAN;
    double y_ = NAN;
    double z_ = NAN;

public:
    Vec3() : x_(0.0), y_(0.0), z_(0.0) {}
    Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}
    Vec3(const Point& p1, const Point& p2) : x_(p2.x_-p1.x_), y_(p2.y_-p1.y_), z_(p2.z_-p1.z_) {}
    Vec3(const Point& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}

    bool is_valid() const { return !((x_ != x_) || (y_ != y_) || (z_ != z_)); }

    double get_x() const { return x_; }
    double get_y() const { return y_; }
    double get_z() const { return z_; }

    Vec3 operator+ (const Vec3& v) const;
    Vec3 operator- (const Vec3& v) const;
    Vec3 operator* (double sqalar) const;
    bool operator==(const Vec3& v) const;
    bool operator!=(const Vec3& v) const;

    double mod() const;
    Vec3 norm() const;
    Vec3 sqalar(double sqalar) const;
    double dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;
    // double angle(const Vec3& v) const { return acos(dot(v)/(this->mod()*v.mod())); }

    bool is_collinear(const Vec3& v) const;
    double similarity_coeff(const Vec3& v) const; // only for collinear vectors

    Geometry2D::Vec2 to_vec2() const;
    Point to_point() const;

    void print(const char* msg) const;
};

class Line
{
    Point   p_  ;
    Vec3    dir_;

public:
    Line() : p_(Point()), dir_(Vec3()) {}
    Line(Point p, Vec3 dir) : p_(p), dir_(dir) {}

    bool is_valid() const { return p_.is_valid() && dir_.is_valid() && (dir_ != Vec3()); }

    Point get_p()   const { return p_  ; }
    Vec3  get_dir() const { return dir_; }

    bool operator==(const Line& l) const;
    bool operator!=(const Line& l) const;

    void print(const char* msg) const;
};

class Plane
{
    Vec3    n_;
    double  d_;

public:
    Plane() : n_(Vec3()), d_(0.0) {}
    Plane(Vec3 n, double d)  :  n_(n), d_(d) {}
    Plane(Vec3 n, const Point& p) : n_(n), d_((-1.0)*n.dot(Vec3(p))) {}
    Plane(const Point& p1, const Point& p2, const Point& p3)
    {
        n_ = Vec3(p1, p2).cross(Vec3(p1, p3));
        d_ = (-1.0)*n_.dot(Vec3(p1));
    }

    bool is_valid() const { return n_.is_valid() && (n_ != Vec3()) && (d_ == d_); }

    double get_d() const { return d_; }
    Vec3   get_n() const { return n_; }

    bool operator==(const Plane& pl) const;
    bool operator!=(const Plane& pl) const;

    bool is_point_on_plane(const Point& p) const;
    bool is_parallel(const Plane& pl) const;
    bool is_parallel(const Vec3& v) const;

    // signed distance between a point and plane
    double signed_distance(const Point& p) const;

    Line intersect(const Plane& pl) const;

    void print(const char* msg) const;
};

class Triangle
{
    Point p1_;
    Point p2_;
    Point p3_;

public:
    Triangle() :  p1_(Point()), p2_(Point()), p3_(Point()) {}
    Triangle(Point p1, Point p2, Point p3) :  p1_(p1), p2_(p2), p3_(p3) {}
    Triangle(Point p1, Point p2) :  p1_(p1), p2_(p2), p3_(p2) {}
    Triangle(Point p) :  p1_(p), p2_(p), p3_(p) {}

    bool is_valid() const { return p1_.is_valid() && p2_.is_valid() && p3_.is_valid(); }

    Point get_p1() const { return p1_; }
    Point get_p2() const { return p2_; }
    Point get_p3() const { return p3_; }

    Plane get_plane() const;

    std::vector<double> signed_distances(const Plane& plane) const;

    Geometry2D::Triangle to_triangle2D() const;

    bool intersect(const Triangle& t) const;

    void print(const char* msg) const;
};

}

#endif
