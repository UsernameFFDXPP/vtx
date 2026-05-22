#include "vtx/vector.hpp"
#include "vtx/matrix.hpp"
#include <iostream>

int main(){
    vtx::Matrix<int> mat1={{1,2,3},{0,1,0}};
    vtx::Vector<int> vec1={1,1};
    std::cout<<mat1.trans()*vec1;
    return 0;
}