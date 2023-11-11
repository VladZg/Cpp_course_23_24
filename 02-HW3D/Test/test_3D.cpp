#include <gtest/gtest.h>
#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

using namespace Geometry3D;

TEST(Point, to_point2D)
{
    // Point p(1.0, 2.0, 3.0);

    Point p1 = Point(1.0, 2.0, 3.0);
    Point p2 = Point(-3.4, -17.9, 14.08);
    Point p3 = Point(6, -2, 4);

    EXPECT_TRUE(p1.to_point2D(2) == Geometry2D::Point(1.0, 2.0));
    EXPECT_TRUE(p2.to_point2D(2) == Geometry2D::Point(-3.4, -17.9));
    EXPECT_TRUE(p3.to_point2D(2) == Geometry2D::Point(6, -2));
}

TEST(Vec3, operator_eq)
{
    Vec3 v1 = Vec3(1.17,-3.4,17.9);
    Vec3 v2 = Vec3(13.4,9.3,1.3);
    Vec3 v3 = Vec3(2.34,-6.8,35.8);
    Vec3 v4 = Vec3(1.17,-3.4,17.9);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 == v4);
    EXPECT_TRUE(v2 != v3);
    EXPECT_TRUE(v2 != v4);
    EXPECT_TRUE(v3 != v4);
    EXPECT_TRUE(v1 == v1);
    EXPECT_TRUE(v2 == v2);
    EXPECT_TRUE(v3 == v3);
}

TEST(Vec3, is_collinear)
{
    Vec3 v1 = Vec3(1.17,-3.4,17.9);
    Vec3 v2 = Vec3(13.4,9.3,1.3);
    Vec3 v3 = Vec3(2.34,-6.8,35.8);
    Vec3 v4 = Vec3(1.17,-3.4,17.9);

    EXPECT_TRUE(v1.is_collinear(v3));
}

TEST(Line, operator_eq)
{
    Line l1 = Line(Point(0,0,0), Vec3(1,1,0));
    Line l2 = Line(Point(1,1,0), Vec3(-1,-1,0));
    Line l3 = Line(Point(11.3,11.3,0), Vec3(24.17, 24.17, 0));

    EXPECT_TRUE(l1 == l2);
    EXPECT_TRUE(l2 == l1);
    EXPECT_TRUE(l1 == l3);
    EXPECT_TRUE(l2 == l3);
    EXPECT_TRUE(l3 == l2);
}

TEST(Plane, operator_eq)
{
    Plane pl1 = Plane(Vec3(1,1,1), 1.2);
    Plane pl2 = Plane(Vec3(-4,-4,-4), -4.8);
    Plane pl3 = Plane(Vec3(-1,-1,-1), -1.2);

    EXPECT_TRUE(pl1 == pl2);
    EXPECT_TRUE(pl2 == pl1);
    EXPECT_TRUE(pl1 == pl3);
    EXPECT_TRUE(pl2 == pl3);
}

TEST(Triangle, to_line_segment)
{
    Point p1(1,0,0);
    Point p2(2,0,0);
    Point p3(3,0,0);
    Triangle t1(p1, p2, p3);

    EXPECT_TRUE(t1.equals_line_segment());
    EXPECT_TRUE(t1.to_line_segment() == LineSegment(Point(3,0,0), Vec3(-2,0,0)));
    EXPECT_TRUE(t1.to_line_segment() != LineSegment(Point(2,0,0), Vec3(-1,0,0)));
    EXPECT_TRUE(t1.to_line_segment() == LineSegment(Point(1,0,0), Vec3(2,0,0)));

    Point p4(1,0,0);
    Point p5(3,1,0);
    Point p6(1,0,0);
    Triangle t2(p4, p5, p6);

    // t2.to_line_segment().print("");

    EXPECT_TRUE(t2.equals_line_segment());
    EXPECT_TRUE(t2.to_line_segment() == LineSegment(Point(1,0,0), Vec3(2,1,0)));
    EXPECT_TRUE(t2.to_line_segment() == LineSegment(Point(3,1,0), Vec3(-2,-1,0)));
    EXPECT_TRUE(t2.to_line_segment() != LineSegment(Point(1,0,0), Vec3(4,2,0)));
}

TEST(LineSegment, intersect_point)
{
    Point p1(1,1,0);
    Point p2(-1,-1,0);
    Point p3(3,3,0);
    Triangle t1(p1, p2, p3);

    Point p4(1,0,0);
    Point p5(3,1,0);
    Point p6(1,0,0);
    Triangle t2(p4, p5, p6);

    EXPECT_TRUE(t1.equals_line_segment());
    // t1.to_line_segment().print("LINE SEGMENT: ");
    EXPECT_TRUE(t1.to_line_segment().intersect(Point(0,0,0)));
}

TEST(Plane, intersect)
{
    Plane plane1 = Plane(Point(1,0,0), Point(0,1,0), Point(0,0,0));
    Plane plane2 = Plane(Point(0,0,0), Point(0,1,0), Point(0,0,1));

    EXPECT_TRUE(plane1.intersect(plane2) == Line(Point(0,0,0), Vec3(0,99,0)));
}

TEST(Triangle, projection_interval)
{
    Point p1(0,0,0);
    Point p2(0,1,0);
    Point p3(1,0,0);
    Triangle t1(p1, p2, p3);

    Point p4(0,0,0);
    Point p5(0,0,1);
    Point p6(0,1,0);
    Triangle t2(p4,p5,p6);

    Plane plane1 = t1.get_plane();
    Plane plane2 = t2.get_plane();

    std::vector<double> sgn_dst1 = t1.signed_distances(plane2);
    std::vector<double> sgn_dst2 = t2.signed_distances(plane1);

    Line intersection_line = plane1.intersect(plane2);

    std::vector<double> interval1 = t1.projection_interval(intersection_line, sgn_dst1);
    std::vector<double> interval2 = t2.projection_interval(intersection_line, sgn_dst2);

    EXPECT_TRUE(t1.intersect(t2));
}

TEST(Triangle, intersect)
{
    Triangle t1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));
    Triangle t2(Point(0.0, 0.0, 0.0), Point(0.0, 5.0, 0.0), Point(5.0, 0.0, 0.0));
    Triangle t3(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 5.0), Point(0.0, -1.0, 5.0));
    Triangle t4(Point(0.0, 0.0, 0.0), Point(0.0, 0.0, 0.0), Point(0.0, 0.0, 0.0));
    Triangle t5(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(0.0, 0.0, 1.0));
    Triangle t6(Point(1.0, 0.0, -2.0), Point(1.0, 0.0, 2.0), Point(1.0, -2.0, 0.0));
    Triangle t7(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(0.0, 2.0, 1.0));
    Triangle t8(Point(0.0, 0.0, 0.0), Point(0.0, 5.0, 0.0), Point(5.0, 0.0, 0.0));
    Triangle t9(Point(0.0, 0.0, 0.0), Point(0.0, 5.0, 0.0), Point(5.0, 0.0, 0.0));

    EXPECT_TRUE(t1.intersect(t2));
    // EXPECT_TRUE(t4.intersect(t4));
    EXPECT_TRUE(t1.intersect(t1));
    // EXPECT_TRUE(t1.intersect(t3));
    // EXPECT_TRUE(t3.intersect(t4));
    EXPECT_TRUE(!t5.intersect(t6));
    EXPECT_TRUE(t1.intersect(t7));
}

TEST(LineSegment, to_line_segment_2D)
{
    Point p = Point(1.43, 22.9, -17.4);
    Vec3 v = Vec3(-1.75, 12.4, 0.0);
    LineSegment ls = LineSegment(p, v);

    Geometry2D::LineSegment ls_2D = ls.to_line_segment_2D(v.max_component_index());
    // ls.print("LINE SEGMENT 3D: ");
    // ls_2D.print("LINE SEGMENT 2D: ");

    EXPECT_TRUE(ls_2D == Geometry2D::LineSegment(Geometry2D::Point(-17.4, 1.43), Geometry2D::Vec2(0.0, -1.75)));
}

TEST(LineSegment, intersect_line_segment)
{
    Point p1 = Point(0,0,0);
    Vec3 v1 = Vec3(1,1,1);
    LineSegment ls1 = LineSegment(p1, v1);

    Point p2 = Point(0,0,0);
    Vec3 v2 = Vec3(-1,-1,-1);
    LineSegment ls2 = LineSegment(p2, v2);

    Point p3 = Point(0,0,-1);
    Vec3 v3 = Vec3(1,1,-1);
    LineSegment ls3 = LineSegment(p3, v3);

    Point p4 = Point(-1,0,0);
    Vec3 v4 = Vec3(0,-1,0);
    LineSegment ls4 = LineSegment(p4, v4);

    Point p5 = Point(0,0,0);
    Vec3 v5 = Vec3(-1,-1,-1);
    LineSegment ls5 = LineSegment(p5, v5);

    // ls.print("LINE SEGMENT 3D: ");
    // ls_2D.print("LINE SEGMENT 2D: ");

    EXPECT_TRUE(ls1.intersect(ls2));
    EXPECT_TRUE(!ls1.intersect(ls3));
    EXPECT_TRUE(ls1.intersect(ls1));
    EXPECT_TRUE(!ls1.intersect(ls4));
    EXPECT_TRUE(ls2.intersect(ls2));
    EXPECT_TRUE(ls3.intersect(ls3));
}

TEST(Triangle, intersect_line_segment)
{
    Triangle t1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));
    LineSegment ls1 = LineSegment(Point(0,0,0), Vec3(0,0,1));

    // Triangle t2(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));
    LineSegment ls2 = LineSegment(Point(0.5,0.5,-1), Vec3(0,0,2));

    // Triangle t1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));
    LineSegment ls3 = LineSegment(Point(0.5,0,0), Vec3(-1,1,0));
    //
    // Triangle t1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));
    LineSegment ls4 = LineSegment(Point(0,0,1), Vec3(0,0,-1));

    EXPECT_TRUE(t1.intersect(ls1));
    EXPECT_TRUE(t1.intersect(ls2));
    EXPECT_TRUE(t1.intersect(ls3));
    EXPECT_TRUE(t1.intersect(ls4));
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//     Geometry3D::Point a{0, 0, 0};
//     Geometry3D::Point b{2, 0, 0};
//     Geometry3D::Point c{0, 2, 0};
//
//     Geometry3D::Vec3 v1{a};
//     Geometry3D::Vec3 v2{b};
//
//     v1.print("Vector #1: ");
//     v2.print("Vector #2: ");
//     (v1+v2).print("v1 + v2: ");
//     (v1-v2).print("v1 - v2: ");
//     std::cout << "v1 * v2: " << v1.dot(v2) << std::endl;
//     v1.cross(v2).print("v1 x v2: ");
//     // std::cout << "angle(v1, v2): " << v1.angle(v2) << std::endl;
//
// //     Geometry2D::Point a{1, 2};
// //     Geometry2D::Point b{2, 3};
// //     Geometry2D::Point c{3, 4};
// //
// //     Geometry2D::Vec2 v1{a, b};
// //     Geometry2D::Vec2 v2{b, c};
// //
// //     v1.print("Vector #1: ");
// //     v2.print("Vector #2: ");
// //     (v1+v2).print("v1 + v2: ");
// //     (v1-v2).print("v1 - v2: ");
// //     std::cout << "(v1, v2): " << v1.dot(v2) << std::endl;
// //     // v1.cross(v2).print("v1 x v2: ");
//
//     Geometry3D::Triangle tr1{a, b, c};
//     tr1.print("Triangle #1: ");
//
//     Geometry3D::Plane plane = tr1.get_plane();
//     plane.print("Triangle #1 is on plane: ");
//
//     if (plane.is_point_on_plane(a)) std::cout << "Point a is on plane\n";
//     if (plane.is_point_on_plane(b)) std::cout << "Point b is on plane\n";
//     if (plane.is_point_on_plane(c)) std::cout << "Point c is on plane\n";
//
//     Geometry3D::Point d = Geometry3D::Point{0, 0, 0};
//     Geometry3D::Point f = Geometry3D::Point{1, 0, 0};
//     Geometry3D::Point e = Geometry3D::Point{0, 1, 0};
//
//     std::cout << "signed distance between point d and plane 1: " << plane.signed_distance(d) << std::endl;
//     std::cout << "signed distance between point f and plane 1: " << plane.signed_distance(f) << std::endl;
//     std::cout << "signed distance between point e and plane 1: " << plane.signed_distance(e) << std::endl;
//
//     Geometry3D::Triangle tr2{d, f, e};
//     tr2.print("Triangle #2: ");
//
//     if (!tr2.intersect(tr1)) std::cout << "Not intersected\n";
//     else std::cout << "Intersected\n";
//
// //     std::cout << "\n\n\n";
// //
// //     // Geometry3D::Plane plane1 = Geometry3D::Plane{Geometry3D::Point(1,2,3), Geometry3D::Point(3,4.5,17), Geometry3D::Point(0,0,0)};
// //     // Geometry3D::Plane plane2 = Geometry3D::Plane{Geometry3D::Point(-1,2,5), Geometry3D::Point(7,3,-1), Geometry3D::Point(0,1,1)};
// //
// //     Geometry3D::Plane plane1 = Geometry3D::Plane{Geometry3D::Vec3{17, 8.9, 93}, -7};
// //     Geometry3D::Plane plane2 = Geometry3D::Plane{Geometry3D::Vec3{13, 0, -4.5}, 0.8};
// //
// //     plane1.print("PLANE 1: ");
// //     plane2.print("PLANE 2: ");
// //     plane1.intersect(plane2).print("INTERSECTION LINE: ");
