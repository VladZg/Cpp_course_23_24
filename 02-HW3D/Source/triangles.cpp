#ifndef GEOMETRY_CPP
#define GEOMETRY_CPP

#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

int main()
{
    Geometry3D::Point a{0, 0, 0};
    Geometry3D::Point b{2, 0, 0};
    Geometry3D::Point c{0, 2, 0};

    Geometry3D::Vec3 v1{a};
    Geometry3D::Vec3 v2{b};

    v1.print("Vector #1: ");
    v2.print("Vector #2: ");
    (v1+v2).print("v1 + v2: ");
    (v1-v2).print("v1 - v2: ");
    std::cout << "v1 * v2: " << v1.dot(v2) << std::endl;
    v1.cross(v2).print("v1 x v2: ");
    // std::cout << "angle(v1, v2): " << v1.angle(v2) << std::endl;

//     Geometry2D::Point a{1, 2};
//     Geometry2D::Point b{2, 3};
//     Geometry2D::Point c{3, 4};
//
//     Geometry2D::Vec2 v1{a, b};
//     Geometry2D::Vec2 v2{b, c};
//
//     v1.print("Vector #1: ");
//     v2.print("Vector #2: ");
//     (v1+v2).print("v1 + v2: ");
//     (v1-v2).print("v1 - v2: ");
//     std::cout << "(v1, v2): " << v1.dot(v2) << std::endl;
//     // v1.cross(v2).print("v1 x v2: ");

    Geometry3D::Triangle tr1{a, b, c};
    tr1.print("Triangle #1: ");

    Geometry3D::Plane plane = tr1.get_plane();
    plane.print("Triangle #1 is on plane: ");

    if (plane.is_point_on_plane(a)) std::cout << "Point a is on plane\n";
    if (plane.is_point_on_plane(b)) std::cout << "Point b is on plane\n";
    if (plane.is_point_on_plane(c)) std::cout << "Point c is on plane\n";

    Geometry3D::Point d = Geometry3D::Point{0, 0, 0};
    Geometry3D::Point f = Geometry3D::Point{1, 0, 0};
    Geometry3D::Point e = Geometry3D::Point{0, 1, 0};

    std::cout << "signed distance between point d and plane 1: " << plane.signed_distance(d) << std::endl;
    std::cout << "signed distance between point f and plane 1: " << plane.signed_distance(f) << std::endl;
    std::cout << "signed distance between point e and plane 1: " << plane.signed_distance(e) << std::endl;

    Geometry3D::Triangle tr2{d, f, e};
    tr2.print("Triangle #2: ");

    if (!tr2.intersection(tr1)) std::cout << "Not intersected\n";
    else std::cout << "Intersected\n";

//     std::cout << "\n\n\n";
//
//     // Geometry3D::Plane plane1 = Geometry3D::Plane{Geometry3D::Point(1,2,3), Geometry3D::Point(3,4.5,17), Geometry3D::Point(0,0,0)};
//     // Geometry3D::Plane plane2 = Geometry3D::Plane{Geometry3D::Point(-1,2,5), Geometry3D::Point(7,3,-1), Geometry3D::Point(0,1,1)};
//
//     Geometry3D::Plane plane1 = Geometry3D::Plane{Geometry3D::Vec3{17, 8.9, 93}, -7};
//     Geometry3D::Plane plane2 = Geometry3D::Plane{Geometry3D::Vec3{13, 0, -4.5}, 0.8};
//
//     plane1.print("PLANE 1: ");
//     plane2.print("PLANE 2: ");
//     plane1.intersection(plane2).print("INTERSECTION LINE: ");

    return 0;
}

#endif
