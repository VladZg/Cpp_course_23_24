#ifndef GEOMETRY_3D_HPP
#define GEOMETRY_3D_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

namespace Geometry3D {

const double EPS = std::numeric_limits<double>::epsilon();

struct Point
{
    double x_ = NAN;
    double y_ = NAN;
    double z_ = NAN;

    Point() : x_(0.0), y_(0.0), z_(0.0) {}
    Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    bool is_valid() const
    {
        return !((x_ != x_) || (y_ != y_) || (z_ != z_));
    }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")";
    }
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

    bool is_valid() const
    {
        return !((x_ != x_) || (y_ != y_) || (z_ != z_));
    }

    Vec3 operator+ (const Vec3& v) const { return Vec3(x_+v.x_, y_+v.y_, z_+v.z_); }
    Vec3 operator- (const Vec3& v) const { return Vec3(x_-v.x_, y_-v.y_, z_-v.z_); }
    Vec3 operator* (double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
    bool operator==(const Vec3& v) const { return fabs(x_-v.x_) < EPS && fabs(y_==v.y_) < EPS && fabs(z_==v.z_) < EPS; }
    bool operator!=(const Vec3& v) const { return !(*this == v); }

    double mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)); }
    Vec3 norm()
    {
        double mod = this->mod();
        return Vec3(x_/mod, y_/mod, z_/mod);
    }

    Vec3 sqalar(double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
    double dot(const Vec3& v) const { return x_*v.x_ + y_*v.y_ + z_*v.z_; }
    Vec3 cross(const Vec3& v) const { return Vec3(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_); }
    // double angle(const Vec3& v) const { return acos(dot(v)/(this->mod()*v.mod())); }

    bool is_collinear(const Vec3& v) const { return cross(v) == Vec3(); }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
    }
};

class Line
{
    Point   p_;
    Vec3    a_;
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

    double get_d() { return d_; }
    Vec3   get_n() { return n_; }

    bool is_point_on_plane(const Point& p) const { return fabs(n_.dot(Vec3(p)) + d_) < EPS; }

    // not a real distance between a point and plane, but has the same sign
    double signed_distance(const Point& point) const { return Vec3(point).dot(n_) + d_; }

    void print(const char* msg = "") const
    {
        std::cout << msg << "n = ";

        n_.print();
        std::cout << "d = " << d_;

        std::cout << std::endl;
    }
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

    Plane get_plane() const { return Plane(p1_, p2_, p3_); }

    std::vector<double> signed_distances(const Plane& plane) const
    {
        return {plane.signed_distance(p1_),
                plane.signed_distance(p2_),
                plane.signed_distance(p3_) };
    }

    bool intersection(const Triangle& t) const
    {
        Plane plane1 = get_plane();
        Plane plane2 = t.get_plane();

        std::vector<double> sgn_dst1 = signed_distances(plane2);
        std::vector<double> sgn_dst2 = t.signed_distances(plane1);

        // check if all the verticles of the 1st triangle are from the one side from the plane of the 2nd
        if (fabs(sgn_dst1[0]) > EPS && fabs(sgn_dst1[1]) > EPS && fabs(sgn_dst1[2]) > EPS)
            if (sgn_dst1[0]*sgn_dst1[1] >= 0.0 && sgn_dst1[1]*sgn_dst1[2] >= 0.0)
                return false;

        // check if all the verticles of the 2nd triangle are from the one side from the plane of the 1st
        if (fabs(sgn_dst2[0]) > EPS && fabs(sgn_dst2[1]) > EPS && fabs(sgn_dst2[2]) > EPS)
            if (sgn_dst2[0]*sgn_dst2[1] >= 0.0 && sgn_dst2[1]*sgn_dst2[2] >= 0.0)
                return false;

        return true;
    }

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
