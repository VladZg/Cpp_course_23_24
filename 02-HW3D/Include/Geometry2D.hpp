#ifndef GEOMETRY_2D_HPP
#define GEOMETRY_2D_HPP

#include <iostream>
#include <cmath>
#include <vector>


namespace Geometry2D
{

const double EPS = 0.000001;

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

    bool is_valid() const
    {
        return !((x_ != x_) || (y_ != y_));
    }

    Vec2 operator+ (const Vec2& v) const { return Vec2(x_+v.x_, y_+v.y_); }
    Vec2 operator- (const Vec2& v) const { return Vec2(x_-v.x_, y_-v.y_); }
    Vec2 operator* (double sqalar) const { return Vec2(x_*sqalar, y_*sqalar); }
    bool operator==(const Vec2& v) const { return fabs(x_-v.x_) < EPS && fabs(y_==v.y_) < EPS; }
    bool operator!=(const Vec2& v) const { return !(*this == v); }

    double mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2)); }

    void norm()
    {
        double mod = this->mod();
        x_ /= mod;
        y_ /= mod;
    }

    double dot(const Vec2& v) const { return x_*v.x_ + y_*v.y_; }
    // Vec3 cross(const Vec3& v) const { return Vec3(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_); }
    double angle(const Vec2& v) const { return acos(dot(v)/(mod()*v.mod())); }

    void print(const char* msg = "") const
    {
        std::cout << msg << "(" << x_ << ", " << y_ << ")" << std::endl;
    }
};

class Line
{
    Point   p_;
    Vec2    v_;

public:

};

class Triangle
{
    std::vector<Point> points_{3};

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
