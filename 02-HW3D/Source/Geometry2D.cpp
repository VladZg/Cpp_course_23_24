#ifndef GEOMETRY_2D_CPP
#define GEOMETRY_2D_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#include "../Include/Geometry2D.hpp"

using namespace Geometry2D;


Point Point::operator+ (const  Point& p) const { return Point(x_+p.x_, y_+p.y_)                    ; }
Point Point::operator- (const  Point& p) const { return Point(x_-p.x_, y_-p.y_)                    ; }
Point Point::operator* (double sqalar  ) const { return Point(sqalar*x_, sqalar*y_)                ; }
Point Point::operator/ (double sqalar  ) const { return Point(x_/sqalar, y_/sqalar)                ; }
bool  Point::operator==(const  Point& p) const { return fabs(x_-p.x_) < EPS && fabs(y_-p.y_) < EPS ; }
bool  Point::operator!=(const  Point& p) const { return !(*this == p)                              ; }

void Point::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ")";
}

Vec2 Geometry2D::vec_line_projection(const Vec2& v, const Line& l)
{
    return l.get_dir().sqalar(v.dot(l.get_dir()));
}

Point Geometry2D::point_line_projection(const Point& p, const Line& l)
{
    Vec2 v_proj = vec_line_projection(Vec2(l.get_p(), p), l);

    return (Vec2(p)+v_proj).to_point();
}


Vec2 Vec2::operator+ (const Vec2& v) const { return Vec2(x_+v.x_, y_+v.y_)                     ; }
Vec2 Vec2::operator- (const Vec2& v) const { return Vec2(x_-v.x_, y_-v.y_)                     ; }
Vec2 Vec2::operator* (double sqalar) const { return Vec2(x_*sqalar, y_*sqalar)                 ; }
Vec2 Vec2::operator/ (double sqalar) const { return Vec2(x_/sqalar, y_/sqalar)                 ; }
bool Vec2::operator==(const Vec2& v) const { return fabs(x_-v.x_) < EPS && fabs(y_-v.y_) < EPS ; }
bool Vec2::operator!=(const Vec2& v) const { return !(*this == v)                              ; }

Point Vec2::to_point() const { return Point(x_, y_); }

double Vec2::mod() const { return fsqrt(dot(*this)); }
Vec2 Vec2::norm() const { return (*this)/mod(); }
Vec2 Vec2::sqalar(double sqalar) const { return Vec2(x_*sqalar, y_*sqalar); }
double Vec2::kross(const Vec2& v) const { return x_*v.y_-y_*v.x_; }
double Vec2::dot(const Vec2& v) const { return x_*v.x_ + y_*v.y_; }
double Vec2::angle(const Vec2& v) const { return fabs(kross(v)/(mod()*v.mod())); };
bool Vec2::is_collinear(const Vec2& v) const { return fabs(x_*v.y_ - y_*v.x_) < EPS; }
double Vec2::similarity_coeff(const Vec2& v) const // only for collinear vectors
{
    // if (!is_collinear(v)) throw ;
    if (fabs(x_)>EPS)
        return v.x_/x_;

    if (fabs(y_)>EPS)
        return v.y_/y_;

    return 0.0;
}

void Vec2::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ")" << std::endl;
}

bool Line::is_parallel(const Line& l) const { return dir_.is_collinear(l.dir_); }
bool Line::intersect(const Line& l) const { return !dir_.is_collinear(l.dir_); }
// bool Line::intersect(const LineSegment& ls) const { return ; }
// bool Line::intersect(const Point& p) const { return Vec2(p,p_).is_collinear(dir_); }

Point Line::intersection_point(const Line& l) const // for non-parallel lines
{
    Vec2 d = Vec2(p_, l.p_);

    double s = d.kross(l.dir_) / dir_.kross(l.dir_);
    Vec2 vi = Vec2(p_) + dir_*s;

    return vi.to_point();
}

bool Line::operator==(const Line& l) const
{
    Vec2 dir = Vec2(p_, l.p_);
    return dir.is_collinear(dir_) && dir.is_collinear(l.dir_);
}
bool Line::operator!=(const Line& l) const { return !(*this == l); }



bool LineSegment::operator==(const LineSegment& l) const { return p_==l.p_ && dir_==l.dir_; }
bool LineSegment::operator!=(const LineSegment& l) const { return !(*this == l)           ; }

bool LineSegment::intersect(const LineSegment& ls) const
{
    Vec2 d = Vec2(p_, ls.p_);

    double rxs = dir_.kross(ls.dir_);
    double dxr = d.kross(dir_);

    if (fabs(rxs) < EPS)
    {
        if (fabs(dxr) < EPS) // line segments are on the same line
        {
            double t0 = d.dot(dir_) / dir_.dot(dir_);
            double t1 = t0 + ls.dir_.dot(dir_) / dir_.dot(dir_);

            if (t0 > t1)
                std::swap(t0, t1);

            return t0 <= 1.0 && t1 >= 0.0;
        }
        else    // line segments are parallel and not intersecting
            return false;
    }
    else    // lines have one intersection point
    {
        double t = d.kross(ls.dir_) / rxs;
        double u = d.kross(dir_) / rxs;
        return t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0;
    }

    return false;
}

void LineSegment::print(const char* msg = "") const
{
    std::cout << msg << "point ";

    p_.print();
    std::cout << ", dir ";
    dir_.print();

    std::cout << std::endl;
}


bool Triangle::operator==(const Triangle& t) const
{
    return (p1_ == t.p1_ && p2_ == t.p2_ && p3_ == t.p3_) ||
           (p1_ == t.p2_ && p2_ == t.p3_ && p3_ == t.p1_) ||
           (p1_ == t.p3_ && p2_ == t.p1_ && p3_ == t.p2_);
}
bool Triangle::operator!=(const Triangle& t) const { return !(*this==t); }

bool Triangle::is_point_inside(const Point &p) const
{
    Vec2 v0 = Vec2(p1_, p3_);
    Vec2 v1 = Vec2(p1_, p2_);
    Vec2 v2 = Vec2(p1_, p  );

    double v0v0 = v0.dot(v0);
    double v0v1 = v0.dot(v1);
    double v0v2 = v0.dot(v2);
    double v1v1 = v1.dot(v1);
    double v1v2 = v1.dot(v2);

    double norm = 1 / (v0v0 * v1v1 - v0v1 * v0v1);
    double u = (v1v1 * v0v2 - v0v1 * v1v2) * norm;
    double v = (v0v0 * v1v2 - v0v1 * v0v2) * norm;

    return (u >= 0.0) && (v >= 0.0) && (u + v <= 1.0);
}

bool Triangle::intersect(const LineSegment &ls) const
{
    if (is_point_inside(ls.get_p()) || is_point_inside(ls.get_p2()))
        return true;

    return ls.intersect(LineSegment(p1_,p2_)) || ls.intersect(LineSegment(p2_, p3_)) || ls.intersect(LineSegment(p3_, p1_));
}

bool Triangle::intersect(const Triangle& t) const
{
    if (is_point_inside(t.p1_) || is_point_inside(t.p2_) || is_point_inside(t.p3_))
        return true;

    if (t.is_point_inside(p1_) || t.is_point_inside(p2_) || t.is_point_inside(p3_))
        return true;

    std::vector<LineSegment> edges1{LineSegment(  p1_,  p2_), LineSegment(  p2_,  p3_), LineSegment(  p3_,  p1_)};
    std::vector<LineSegment> edges2{LineSegment(t.p1_,t.p2_), LineSegment(t.p2_,t.p3_), LineSegment(t.p3_,t.p1_)};

    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
        int i_next = (i + 1) % 3;
        int j_next = (j + 1) % 3;
        if (edges1[i_next].intersect(edges2[j_next]))
            return true;
    }

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
