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
    Point p5(0,1,0);
    Point p6(0,0,1);
    Triangle t2(p4,p5,p6);

    Plane plane1 = t1.get_plane();
    Plane plane2 = t2.get_plane();

    std::vector<double> sgn_dst1 = t1.signed_distances(plane2);
    std::vector<double> sgn_dst2 = t2.signed_distances(plane1);

    Line intersection_line = plane1.intersect(plane2);

    std::vector<double> interval1 = t1.projection_interval(intersection_line, sgn_dst1);
    std::vector<double> interval2 = t2.projection_interval(intersection_line, sgn_dst2);

    // EXPECT_TRUE(t1.intersect(t2));
}

TEST(Triangle, intersect)
{
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t1(p1, p2, p3);

    Point p4(0.0, 0.0, 0.0);
    Point p5(0.0, 5.0, 0.0);
    Point p6(5.0, 0.0, 0.0);
    Triangle t2(p4,p5,p6);

    EXPECT_TRUE(t1.intersect(t2));
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
