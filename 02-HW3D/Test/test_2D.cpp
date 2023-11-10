#include <gtest/gtest.h>
#include "../Include/Geometry2D.hpp"

using namespace Geometry2D;

TEST(Line, is_parallel)
{
    Line l1 = Line(Point(2,2), Vec2(1,1));
    Line l2 = Line(Point(17,17), Vec2(-4,-4));
    Line l3 = Line(Point(9,1), Vec2(1,0));

    EXPECT_TRUE(l1.is_parallel(l2));
    EXPECT_TRUE(l2.is_parallel(l2));
    EXPECT_TRUE(!l1.is_parallel(l3));
    EXPECT_TRUE(l2.is_parallel(l1));
}

TEST(Line, intersection_point)
{
    Line l1 = Line(Point(0,0), Vec2(1,1));
    Line l2 = Line(Point(0,0), Vec2(4,-4));
    Line l3 = Line(Point(5,5), Vec2(19,-0.34));

    EXPECT_TRUE(l1.intersection_point(l2) == Point(0,0));
    EXPECT_TRUE(l1.intersection_point(l3) == Point(5,5));
    EXPECT_TRUE(l2.intersection_point(l3) == Point(-(5.0*933.0+170.0)/933.0, (5.0*933.0+170.0)/933.0));
    EXPECT_TRUE(l2.intersection_point(l1) == Point(0,0));
    EXPECT_TRUE(l3.intersection_point(l1) == Point(5,5));
    EXPECT_TRUE(l3.intersection_point(l2) == Point(-(5.0*933.0+170.0)/933.0, (5.0*933.0+170.0)/933.0));
}

TEST(LineSegment, intersect)
{
    LineSegment ls1 = LineSegment(Point(0,0), Point(1,0));
    LineSegment ls2 = LineSegment(Point(1,0), Point(2,1));
    LineSegment ls3 = LineSegment(Point(0.5,0), Point(0,0.5));

    EXPECT_TRUE(ls1.intersect(ls3));
    EXPECT_TRUE(ls3.intersect(ls1));
    EXPECT_TRUE(ls1.intersect(ls2));
    EXPECT_TRUE(ls2.intersect(ls1));
    EXPECT_TRUE(!ls2.intersect(ls3));
    EXPECT_TRUE(!ls3.intersect(ls2));
}

TEST(Triangle, is_point_inside)
{
    Triangle t1 = Triangle(Point(0,0), Point(1,0), Point(0,1));
    Triangle t2 = Triangle(Point(0,0), Point(1,0), Point(0,1));
    Triangle t3 = Triangle(Point(0,0), Point(-1,0), Point(0,-1));
    Triangle t4 = Triangle(Point(1,-3), Point(-3,2), Point(5,5));

    Point p1 = Point(0,0);
    Point p2 = Point(-1,0);

    EXPECT_TRUE(t1.is_point_inside(p1));
    EXPECT_TRUE(t2.is_point_inside(p1));
    EXPECT_TRUE(t3.is_point_inside(p1));
    EXPECT_TRUE(t4.is_point_inside(p1));
    EXPECT_TRUE(!t1.is_point_inside(p2));
    EXPECT_TRUE(!t2.is_point_inside(p2));
    EXPECT_TRUE(t3.is_point_inside(p2));
}

// TEST(Triangle, intersect)
// {
//     Triangle t1 = Triangle(Point(0,0), Point(1,0), Point(0,1));
//     Triangle t2 = Triangle(Point(0,0), Point(1,0), Point(0,1));
//     Triangle t3 = Triangle(Point(0,0), Point(-1,0), Point(0,-1));
//     Triangle t4 = Triangle(Point(1,-3), Point(-3,2), Point(5,5));
//     Triangle t5 = Triangle(Point(-1,-1), Point(-17,-4), Point(-5,-19));
//
//     EXPECT_TRUE(t1.intersect(t2));
//     EXPECT_TRUE(t2.intersect(t1));
//     EXPECT_TRUE(t1.intersect(t3));
//     EXPECT_TRUE(t3.intersect(t2));
//     EXPECT_TRUE(t1.intersect(t4));
//     EXPECT_TRUE(t4.intersect(t2));
//     EXPECT_TRUE(t3.intersect(t4));
//     EXPECT_TRUE(!t1.intersect(t5));
//
//     Triangle triangle1(Point(0, 0), Point(0, 2), Point(2, 0));
//     Triangle triangle2(Point(1, 1), Point(1, 3), Point(3, 1));
//     EXPECT_TRUE(triangle1.intersect(triangle2));
//
//     // Test two triangles that do not intersect
//     Triangle triangle3(Point(0, 0), Point(0, 2), Point(2, 0));
//     Triangle triangle4(Point(3, 3), Point(3, 4), Point(4, 3));
//     EXPECT_FALSE(triangle3.intersect(triangle4));
//
//     // Test two triangles that share an edge
//     Triangle triangle5(Point(0, 0), Point(0, 2), Point(2, 0));
//     Triangle triangle6(Point(0, 2), Point(2, 0), Point(2, 2));
//     EXPECT_TRUE(triangle5.intersect(triangle6));
//
//     // Test two triangles that share a vertex
//     Triangle triangle7(Point(0, 0), Point(0, 2), Point(2, 0));
//     Triangle triangle8(Point(0, 0), Point(2, 0), Point(2, 2));
//     EXPECT_TRUE(triangle7.intersect(triangle8));
//
//     // Test two triangles that are identical
//     Triangle triangle9(Point(0, 0), Point(0, 2), Point(2, 0));
//     Triangle triangle10(Point(0, 0), Point(0, 2), Point(2, 0));
//     EXPECT_TRUE(triangle9.intersect(triangle10));
// }

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
