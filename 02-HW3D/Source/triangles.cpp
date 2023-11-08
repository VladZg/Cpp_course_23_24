#ifndef GEOMETRY_CPP
#define GEOMETRY_CPP

#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

int main()
{
    Geometry3D::Point a{1, 2, 3};
    Geometry3D::Point b{2, 3, 4};
    Geometry3D::Point c{3, 4, 5};

    Geometry3D::Vec3 v1(a, b);
    Geometry3D::Vec3 v2(b, c);

    v1.print("Vector #1: ");
    v2.print("Vector #2: ");
    (v1+v2).print("v1 + v2: ");
    (v1-v2).print("v1 - v2: ");
    std::cout << "v1 * v2: " << v1.dot(v2) << std::endl;
    v1.cross(v2).print("v1 x v2: ");
    std::cout << "angle(v1, v2): " << v1.angle(v2) << std::endl;

    Geometry3D::Triangle tr{std::vector<Geometry3D::Point>{a, b, c}};

    tr.print("Triangle #1: ");

    return 0;
}

#endif
