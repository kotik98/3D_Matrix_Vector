#include <iostream>
#include "Vector3D.h"

int main() {
    std::cout << "=== Test vector ===" << std::endl;

    Vector3D<int> v1 = {1, 1, 1};
    Vector3D<int> v2 = {2, 2, 2};

    std::cout << (v1 + v2) << std::endl;
    std::cout << (v1 - v2) << std::endl;
    std::cout << v1 * 5 << std::endl;
    std::cout << -5 * v2 << std::endl;
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    std::cout << v1 * v2 << std::endl;
    vector< vector<int> > arg1;
    vector< vector<int> > arg2;
    arg1.resize(3);
    arg2.resize(3);
    for (int i = 0; i < 3; i++){
        arg1[i].resize(3);
        arg2[i].resize(3);
    }
    arg1 =  {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    arg2 = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    Matrix3D<int> m1(arg1);
    Matrix3D<int> m2(arg2);
    std::cout << "=== Test matrix ===" << std::endl;

    std::cout << (m1 + m2) << std::endl;
    std::cout << (m1 - m2) << std::endl;
    std::cout << m1 * 5 << std::endl;
    std::cout << -5 * m2 << std::endl;
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m1 * m2 << std::endl;
    std::cout << m1.determinant() << std::endl;

    std::cout << "=== Cross test vector and matrix ===" << std::endl;

    std::cout << m1 * v1 << std::endl;

    return 0;
}
