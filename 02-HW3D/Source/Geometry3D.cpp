#ifndef GEOMETRY_3D_CPP
#define GEOMETRY_3D_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

using namespace Geometry3D;


bool Point::operator==(const Point& p) const { return fabs(x_-p.x_) < EPS && fabs(y_-p.y_) < EPS && fabs(z_-p.z_) < EPS; }
bool Point::operator!=(const Point& p) const { return !(*this == p); }

Geometry2D::Point Point::to_point2D(short axis_index) const
{
    std::vector<double> coords = {x_, y_, z_};

    int axis1_index = (axis_index+1) % 3;
    int axis2_index = (axis_index+2) % 3;

    return Geometry2D::Point(coords[axis1_index], coords[axis2_index]);
}

void Point::print(const char* msg = "") const
{
    std::cout << msg << "(" << x_ << ", " << y_ << ", " << z_ << ")";
}


Vec3 Vec3::operator+ (const Vec3& v) const { return Vec3(x_+v.x_, y_+v.y_, z_+v.z_); }
Vec3 Vec3::operator- (const Vec3& v) const { return Vec3(x_-v.x_, y_-v.y_, z_-v.z_); }
Vec3 Vec3::operator* (double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
bool Vec3::operator==(const Vec3& v) const { return fabs(x_-v.x_) < EPS && fabs(y_-v.y_) < EPS && fabs(z_-v.z_) < EPS; }
bool Vec3::operator!=(const Vec3& v) const { return !(*this == v); }

short Vec3::max_component_index() const
{
    std::vector<double> components_mod = {fabs(x_), fabs(y_), fabs(z_)};
    return (components_mod[0] >= components_mod[1]) ? ((components_mod[0] >= components_mod[2]) ? 0 : 2) : ((components_mod[1] >= components_mod[2]) ? 1 : 2 );
}

double Vec3::mod() const { return fsqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)); }
Vec3 Vec3::norm() const { double mod = this->mod(); return Vec3(x_/mod, y_/mod, z_/mod); }
Vec3 Vec3::sqalar(double sqalar) const { return Vec3(x_*sqalar, y_*sqalar, z_*sqalar); }
double Vec3::dot(const Vec3& v) const { return x_*v.x_ + y_*v.y_ + z_*v.z_; }
Vec3 Vec3::cross(const Vec3& v) const { return Vec3(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_); }
double Vec3::mixed(const Vec3& v1, const Vec3& v2) const { return dot(v1.cross(v2)); }
double Vec3::cos_angle(const Vec3& v) const { return dot(v)/(mod()*v.mod()); }

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

Geometry2D::Vec2 Vec3::to_vec2(short axis_index) const
{
    std::vector<double> coords = {x_, y_, z_};

    int axis1_index = (axis_index+1) % 3;
    int axis2_index = (axis_index+2) % 3;

    return Geometry2D::Vec2(coords[axis1_index], coords[axis2_index]);
}

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


bool LineSegment::operator==(const LineSegment& ls) const { return (p_==ls.p_ && dir_==ls.dir_) || (Vec3(p_,ls.p_)==dir_ && Vec3(ls.p_,p_)==ls.dir_); }
bool LineSegment::operator!=(const LineSegment& ls) const { return !(*this == ls)            ; }

Geometry2D::LineSegment LineSegment::to_line_segment_2D(short axis_index) const
{
    return Geometry2D::LineSegment(p_.to_point2D(axis_index), dir_.to_vec2(axis_index));
}

bool LineSegment::is_parallel(const LineSegment& ls) const
{
    return dir_.is_collinear(ls.dir_);
}

bool LineSegment::is_coplanar(const LineSegment& ls) const
{
    return fabs(Vec3(p_, ls.p_).mixed(dir_, ls.dir_)) < EPS;
}

// bool LineSegment::is_on_the_same_line(const LineSegment& ls) const  // for parallel vectors
// {
//     return fabs(Vec3(p_, ls.p_).mixed(dir_, ls.dir_)) < EPS;
// }

bool LineSegment::intersect(const Point& p) const
{
    Vec3 d = Vec3(p_, p);

    if (!d.is_collinear(dir_))
        return false;

    double t = dir_.similarity_coeff(d);

    return t >= 0.0 && t <= 1.0;
}

bool LineSegment::intersect(const LineSegment& ls) const
{
    Vec3 d = Vec3(p_, ls.p_);

    if (fabs(d.mixed(dir_, ls.dir_)) > EPS) // if crossed
        return false;

    if (is_parallel(ls))    // if parallel
    {
        if (!d.is_collinear(dir_))   // not lying on the same line
            return false;

        // lying on the same line
        double dir2 = dir_.dot(dir_);
        double t0 = d.dot(dir_) / dir2;
        double t1 = t0 + ls.dir_.dot(dir_) / dir2;

        if (t0 > t1)
            std::swap(t0, t1);

        return t0 <= 1.0 && t1 >= 0.0;
    }

    // coplanar and have an intersection point
    Vec3 n = dir_.cross(ls.dir_);
    short axis_index = n.max_component_index();

    Geometry2D::LineSegment ls1_2D = to_line_segment_2D(axis_index);
    Geometry2D::LineSegment ls2_2D = ls.to_line_segment_2D(axis_index);

    return ls1_2D.intersect(ls2_2D);
}

void LineSegment::print(const char* msg = "") const
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

std::vector<double> Triangle::projection_interval(const Line& l, const std::vector<double>& sgn_dst) const // all sgn_dst are not 0 at the same time
{
    std::vector<double> interval(2);  // line segment projection of the triangle on the line

    Vec3 d = l.get_dir();
    std::vector<double> projections = {d.dot(Vec3(p1_)), d.dot(Vec3(p2_)), d.dot(Vec3(p3_))};

    short index_left = 0;
    short index_right = 0;

    double max_proj = projections[0];
    double min_proj = projections[0];

    for (int i = 0; i < 3; ++i)
    {
        if (projections[i] > max_proj)
            index_right = i;

        else if (projections[i] < min_proj)
            index_left = i;
    }

    short index_middle = 3 - (index_left + index_right);  // index ot the middle project point

    // std::cout << "(" << projections[0] << ", " << projections[1] << ", " << projections[2] \
              << "), right = " << index_right << ", left = " << index_left << ", middle = " << index_middle << "\n";

    if (fabs(sgn_dst[index_left ] - sgn_dst[index_middle]) < EPS) // check if these 2 points are on the line
    {
        interval[0] = projections[index_left ]; // because line direction vector is normalized
        interval[1] = projections[index_right] + (projections[index_middle] - projections[index_right]) * sgn_dst[index_right] / (sgn_dst[index_right] - sgn_dst[index_middle]);
    }

    else if (fabs(sgn_dst[index_right ] - sgn_dst[index_middle]) < EPS) // check if these 2 points are on the line
    {
        interval[0] = projections[index_left ] + (projections[index_middle] - projections[index_left ]) * sgn_dst[index_left ] / (sgn_dst[index_left ] - sgn_dst[index_middle]);
        interval[1] = projections[index_right];
    }

    else
    {
        interval[0] = projections[index_left ] + (projections[index_middle] - projections[index_left ]) * sgn_dst[index_left ] / (sgn_dst[index_left ] - sgn_dst[index_middle]);
        interval[1] = projections[index_right] + (projections[index_middle] - projections[index_right]) * sgn_dst[index_right] / (sgn_dst[index_right] - sgn_dst[index_middle]);
    }

    if (interval[0] > interval[1])
        std::swap(interval[0], interval[1]);

    // std::cout << "interval: [" << interval[0] << "," << interval[1] << "]\n";

    return interval;
}

bool Triangle::equals_point() const { return (p1_ == p2_) && (p2_ == p3_); }
bool Triangle::equals_line_segment() const { return Vec3(p1_, p2_).is_collinear(Vec3(p1_,p3_)); }

Point Triangle::to_point() const { return Point(p1_); }

LineSegment Triangle::to_line_segment() const   // after check that it equals line segment
{
    std::vector<Point> points = {p1_, p2_, p3_};
    std::vector<Vec3> dirs = {Vec3(p1_, p2_), Vec3(p2_, p3_), Vec3(p3_, p1_)};
    std::vector<double> dirs_mod = {Vec3(p1_, p2_).mod(), Vec3(p2_, p3_).mod(), Vec3(p3_, p1_).mod()};

    short index_max = 0;
    double max_mod = dirs_mod[0];

    for (int i = 0; i < 3; ++i)
        if (dirs_mod[i] > max_mod)
            index_max = i;

    return LineSegment(points[index_max], dirs[index_max]);
}

Geometry2D::Triangle Triangle::to_triangle2D(short axis_index) const
{
    return Geometry2D::Triangle(p1_.to_point2D(axis_index),
                                p2_.to_point2D(axis_index),
                                p3_.to_point2D(axis_index));
}

bool Triangle::intersect(const Point &p) const
{
    Plane pl = get_plane();

    if (!pl.is_point_on_plane(p))
        return false;

    short axis_index = pl.get_n().max_component_index();
    Geometry2D::Triangle t_2D = to_triangle2D(axis_index);
    Geometry2D::Point p_2D = p.to_point2D(axis_index);

    return t_2D.is_point_inside(p_2D);
}

bool Triangle::intersect(const LineSegment& ls) const   // REWRITE THIS METHOD
{
    Vec3 v1 = Vec3(p1_, p2_);
    Vec3 v2 = Vec3(p1_, p3_);
    Vec3 d = ls.get_dir();

    Vec3 n = v1.cross(v2);
    Vec3 h = d.cross(v2);
    double a = v1.dot(h);

    if (fabs(d.dot(n)) < EPS)
    {
        if (fabs((Vec3(p1_, ls.get_p())).dot(n)) > EPS)
            return false;

        short axis_index = n.max_component_index();

        Geometry2D::Triangle    t_2D  = to_triangle2D(  axis_index);
        Geometry2D::LineSegment ls_2D = ls.to_line_segment_2D(axis_index);

        return t_2D.intersect(ls_2D);
    }

    double f = 1.0 / a;
    Vec3 s = Vec3(p1_, ls.get_p());
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return false;

    Vec3 q = s.cross(v1);
    double v = f * d.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * v2.dot(q);
    return t >= 0.0 && t <= 1.0;
}

bool Triangle::intersect(const Triangle& t) const
{
    Plane plane1 = get_plane();
    Plane plane2 = t.get_plane();

    std::vector<double> sgn_dst1 = signed_distances(plane2);

    // check if all the verticles of the 1st triangle are from the one side from the plane of the 2nd
    if (fabs(sgn_dst1[0]) > EPS && fabs(sgn_dst1[1]) > EPS && fabs(sgn_dst1[2]) > EPS)
        if (sgn_dst1[0]*sgn_dst1[1] >= 0.0 && sgn_dst1[1]*sgn_dst1[2] >= 0.0)
            return false;

    std::vector<double> sgn_dst2 = t.signed_distances(plane1);

    // check if all the verticles of the 2nd triangle are from the one side from the plane of the 1st
    if (fabs(sgn_dst2[0]) > EPS && fabs(sgn_dst2[1]) > EPS && fabs(sgn_dst2[2]) > EPS)
        if (sgn_dst2[0]*sgn_dst2[1] >= 0.0 && sgn_dst2[1]*sgn_dst2[2] >= 0.0)
            return false;

    // check if triangles are co-planar, then check their 2D intersection
    if (fabs(sgn_dst1[0]) < EPS && fabs(sgn_dst1[1]) < EPS && fabs(sgn_dst1[2]) < EPS)
    {
        // finding axis to project on

        short axis_index = plane1.get_n().max_component_index();

        Geometry2D::Triangle t1_2D = to_triangle2D(axis_index);
        Geometry2D::Triangle t2_2D = t.to_triangle2D(axis_index);

        return t1_2D.intersect(t2_2D);
    }

    Line intersection_line = plane1.intersect(plane2);

    std::vector<double> interval1 =   projection_interval(intersection_line, sgn_dst1);
    std::vector<double> interval2 = t.projection_interval(intersection_line, sgn_dst2);

    // std::cout << "interval1: [" << interval1[0] << "," << interval1[1] << "]\n";
    // std::cout << "interval2: [" << interval2[0] << "," << interval2[1] << "]\n";

    return (interval1[0] <= interval2[1]) && (interval2[0] <= interval1[1]);
}

TriangleDegenerationType Triangle::degeneration_type() const
{
    if (equals_point())
        return POINT_TYPE;

    if (equals_line_segment())
        return LINE_SEGMENT_TYPE;

    return TRIANGLE_TYPE;
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
