#ifndef GEOMETRY_3D_CPP
#define GEOMETRY_3D_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

using namespace Geometry3D;


bool Point::operator==(const Point& p) const { return fabs(x_-p.x_) < EPS && fabs(y_==p.y_) < EPS && fabs(z_==p.z_) < EPS; }
bool Point::operator!=(const Point& p) const { return !(*this == p); }

Geometry2D::Point Point::to_point2D() const { return Geometry2D::Point(x_, y_); }

void Point::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")";
}


Vec3 Vec3::operator+ (const Vec3& v) const { return Vec3(x_+v.x_, y_+v.y_, z_+v.z_); }
Vec3 Vec3::operator- (const Vec3& v) const { return Vec3(x_-v.x_, y_-v.y_, z_-v.z_); }
Vec3 Vec3::operator* (double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
bool Vec3::operator==(const Vec3& v) const { return fabs(x_-v.x_) < EPS && fabs(y_-v.y_) < EPS && fabs(z_-v.z_) < EPS; }
bool Vec3::operator!=(const Vec3& v) const { return !(*this == v); }

double Vec3::mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)); }
Vec3 Vec3::norm() const { double mod = this->mod(); return Vec3(x_/mod, y_/mod, z_/mod); }
Vec3 Vec3::sqalar(double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
double Vec3::dot(const Vec3& v) const { return x_*v.x_ + y_*v.y_ + z_*v.z_; }
Vec3 Vec3::cross(const Vec3& v) const { return Vec3(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_); }
// double angle(const Vec3& v) const { return acos(dot(v)/(this->mod()*v.mod())); }

bool Vec3::is_collinear(const Vec3& v) const { return cross(v) == Vec3(); }
double Vec3::similarity_coeff(const Vec3& v) const // only for collinear vectors
{
    // if (!is_collinear(v)) throw ;
    if (fabs(x_)>EPS)
        return v.x_/x_;

    if (fabs(y_)>EPS)
        return v.y_/y_;

    if (fabs(z_)>EPS)
        return v.z_/z_;

    return 0.0;
}

Geometry2D::Vec2 Vec3::to_vec2() const { return Geometry2D::Vec2(x_, y_); }
Point Vec3::to_point() const { return Point(x_, y_, z_); }

void Vec3::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}


bool Line::operator==(const Line& l) const
{
    Vec3 dir = Vec3(p_, l.p_);
    return dir.is_collinear(dir_) && dir.is_collinear(l.dir_);
}
bool Line::operator!=(const Line& l) const { return !(*this == l); }

void Line::print(const char* msg = "") const
{
    std::cout << msg << "point ";

    p_.print();
    std::cout << ", dir ";
    dir_.print();

    std::cout << std::endl;
}


bool Plane::operator==(const Plane& pl) const { return n_.is_collinear(pl.n_) && n_.similarity_coeff(pl.n_)*d_ == pl.d_; }
bool Plane::operator!=(const Plane& pl) const { return !(*this == pl); }

bool Plane::is_point_on_plane(const Point& p) const { return fabs(n_.dot(Vec3(p)) + d_) < EPS; }
bool Plane::is_parallel(const Plane& pl) const { return n_.is_collinear(pl.n_); }
bool Plane::is_parallel(const Vec3& v) const { return fabs(n_.dot(v)) < EPS; }

// signed distance between a point and plane
double Plane::signed_distance(const Point& p) const { return (Vec3(p).dot(n_) + d_) / n_.mod(); }

Line Plane::intersect(const Plane& pl) const
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

void Plane::print(const char* msg = "") const
{
    std::cout << msg << "n = ";

    n_.print();
    std::cout << "d = " << d_;

    std::cout << std::endl;
}


Plane Triangle::get_plane() const { return Plane(p1_, p2_, p3_); }

std::vector<double> Triangle::signed_distances(const Plane& plane) const
{
    return {plane.signed_distance(p1_),
            plane.signed_distance(p2_),
            plane.signed_distance(p3_) };
}

Geometry2D::Triangle Triangle::to_triangle2D() const
{
    return Geometry2D::Triangle(p1_.to_point2D(),
                                p2_.to_point2D(),
                                p3_.to_point2D());
}

bool Triangle::intersect(const Triangle& t) const
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

        return t1_2D.intersect(t2_2D);
    }

    Line intersection_line = plane1.intersect(plane2);
    //

    return false;
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
