#include "vtx/Vector.hpp"
#include "vtx/Matrix.hpp"
#include <iostream>

int main(){
    int a=2;
    vtx::Matrix<int> mat1={{0,1,2},{1,1,2},{2,1,2}};
    vtx::Vector<int> vec1={0,1,2,3};
    std::cout<<mat1.slice({1,3},{0,2});
    std::cout<<vec1.slice({1,3});
    return 0;
}