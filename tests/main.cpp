#include "vtx/vector.hpp"
#include "vtx/matrix.hpp"
#include <iostream>

double cal(double a,double b){
    return a+b;
}

int main(){
    vtx::Matrix mat1={{1,2,3},{0,1,1}};
    vtx::Matrix mat2={{1,0},{0,1},{1,1}};
    auto v11=mat1.toVector(true);
    auto v12=mat1.toVector(false);
    auto v21=mat2.toVector(true);
    auto v22=mat2.toVector(false);
    for(vtx::Vector vct:v11){
        std::cout<<vct;
    }
    for(vtx::Vector vct:v12){
        std::cout<<vct;
    }
    for(vtx::Vector vct:v21){
        std::cout<<vct;
    }
    for(vtx::Vector vct:v22){
        std::cout<<vct;
    }
    return 0;
}