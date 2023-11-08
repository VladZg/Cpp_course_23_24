#ifndef GEOMETRY_3D_HPP
#define GEOMETRY_3D_HPP

#include <iostream>
#include <cmath>
#include <vector>

namespace Geometry3D {

const double EPS = 0.000001;

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
    Vec3(Point& p1, Point& p2) : x_(p2.x_-p1.x_), y_(p2.y_-p1.y_), z_(p2.z_-p1.z_) {}

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

    void norm()
    {
        double mod = this->mod();
        x_ /= mod;
        y_ /= mod;
        z_ /= mod;
    }

    double dot(const Vec3& v) const { return x_*v.x_ + y_*v.y_ + z_*v.z_; }
    Vec3 cross(const Vec3& v) const { return Vec3(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_); }
    double angle(const Vec3& v) const { return acos(dot(v)/(this->mod()*v.mod())); }

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
    Point   p_;
    Vec3    n_;
};

class Triangle
{
    std::vector<Point> points_;

//     bool is_vector_valid(const std::vector< Point>* points) const
//     {
//         if (points->size() != 3)
//             return false;
//
//         for (size_t i = 0; i < 3; i++)
//         {
//             if (!(*points)[i].is_valid())
//                 return false;
//         }
//
//         return true;
//     }

public:

    Triangle(std::vector<Point> points)
    {
        // if (is_vector_valid(&points_))
            points_ = points;

        // else
        //     points = std::vector<Point> {{NAN, NAN}, {NAN, NAN}, {NAN, NAN}};
    }

//     bool is_valid() const
//     {
//         const std::vector<Point>* points_ptr = &points_;
//
//         return is_vector_valid(points_ptr);
//     }

    void print(const char* msg = "") const
    {
        std::cout << msg;

        for (size_t i = 0; i < 3; i++)
        {
            points_[i].print();
            std::cout << " ";
        }

        std::cout << std::endl;
    }
};

}

#endif
