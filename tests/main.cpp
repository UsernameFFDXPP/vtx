#include"vtx/Vector.hpp"
#include"vtx/Matrix.hpp"
#include"vtx/Range.hpp"
#include"vtx/View.hpp"
#include<iostream>

int main(){
    vtx::Matrix<int> mat1={{1,1},{0,1}};
    vtx::Matrix<int> mat2={{1,0},{1,1}};
    vtx::View<int> view1={&mat1};
    vtx::View<int> view2={&mat2};
    vtx::View<int> view3=view1*view2;
    vtx::ViewCache<int> cache1=view3.toCache();
    std::cout<<mat1<<mat2;
    std::cout<<cache1.eval();
    return 0;
}