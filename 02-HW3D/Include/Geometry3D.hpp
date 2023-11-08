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

    Geometry2D::Point to_point2D() const { return Geometry2D::Point(x_, y_); }

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

    double get_x() const { return x_; }
    double get_y() const { return y_; }
    double get_z() const { return z_; }

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

    Point to_point() const { return Point(x_, y_, z_); }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
    }
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

    void print(const char* msg = "") const
    {
        std::cout << msg << "point ";

        p_.print();
        std::cout << ", dir ";
        dir_.print();

        std::cout << std::endl;
    }
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
    bool is_parallel(const Plane& pl) { return n_.is_collinear(pl.n_); }
    bool is_parallel(const Vec3& v) const { return fabs(n_.dot(v)) < EPS; }

    // signed distance between a point and plane
    double signed_distance(const Point& p) const { return (Vec3(p).dot(n_) + d_) / n_.mod(); }

    Line intersection(const Plane& pl)
    {
        // if (is_parallel(pl))            // can't find line
        // {
        //     // std::cout << "PLANES ARE ";
        //     return Line(Point(), Vec3());
        // }

        Vec3 dir = n_.cross(pl.n_);

        double n1n2 = n_.dot(pl.n_);
        double n1n1 = n_.dot(n_);
        double n2n2 = pl.n_.dot(pl.n_);
        double norm = n1n2*n1n2 - n1n1*n2n2;
        double a = ((-pl.d_)*n1n2 - (-d_)*n2n2) / norm;
        double b = ((-d_)*n1n2 - (-pl.d_)*n1n1) / norm;

        Point p = Point(a*n_.get_x() + b*pl.n_.get_x(),
                        a*n_.get_y() + b*pl.n_.get_y(),
                        a*n_.get_z() + b*pl.n_.get_z() );

        return Line(p, dir);
    }

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

    Geometry2D::Triangle to_triangle2D() const
    {
        return Geometry2D::Triangle(p1_.to_point2D(),
                                    p2_.to_point2D(),
                                    p3_.to_point2D());
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

        if (fabs(sgn_dst1[0]) < EPS && fabs(sgn_dst1[1]) < EPS && fabs(sgn_dst1[2]) < EPS)
        {
            // triangles are co-planar, check their 2D intersection
            Geometry2D::Triangle t1_2D = to_triangle2D();
            Geometry2D::Triangle t2_2D = t.to_triangle2D();

            return t1_2D.intersection(t2_2D);
        }

        Line intersection_line = plane1.intersection(plane2);

        return false;
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
