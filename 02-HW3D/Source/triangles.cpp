#ifndef GEOMETRY_CPP
#define GEOMETRY_CPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include "../Include/Geometry2D.hpp"
#include "../Include/Geometry3D.hpp"

using namespace Geometry3D;

void input_triangles(int n, std::vector<Triangle>& fig_arr, std::ifstream& in_file)
{
    std::vector<Point> tr_points(3);
    int x, y, z;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            in_file >> x >> y >> z;
            // std::cout << "(" << x << ", " << y << ", " << z << ")\n";
            tr_points[j] = Point(x, y, z);
        }

        Triangle tr = Triangle(tr_points[0], tr_points[1], tr_points[2]);
        fig_arr.push_back(tr);
    }
}

bool intersect_figures(const Triangle& t1, const Triangle& t2)
{
    return t1.intersect(t2);
}

void intersect_all(const std::vector<Triangle>& fig_arr, std::unordered_set<int> index_set)
{
    int n = fig_arr.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if(intersect_figures(fig_arr[i], fig_arr[j]))
            {
                std::cout << "INTERSECTION: triangle " << i << " with triangle " << j << ":\n";
                fig_arr[i].print("");
                fig_arr[j].print("");
                std::cout << std::endl;

                index_set.insert(i);
                index_set.insert(j);
            }
        }
    }
}

int main()
{
    std::ifstream in_file;
    in_file.open("../Test/test_data.txt");

    if (in_file.is_open())
    {

    std::vector<Triangle> fig_arr;

    int n;
    in_file >> n;
    input_triangles(n, fig_arr, in_file);

    in_file.close();

    std::unordered_set<int> index_set;

    intersect_all(fig_arr, index_set);

    std::vector<int> index_vec;
    index_vec.insert(index_vec.begin(), index_set.begin(), index_set.end());
    std::sort(index_vec.begin(), index_vec.end());

    std::cout << "Indexes of triangles that intersects: ";
    // using SetIt = typename std::unordered_set<int>::iterator;
    for (auto it  = index_vec.begin(); it != index_vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    } else std::cerr << "Problem in opening file with test data\n";

    return 0;
}

#endif
