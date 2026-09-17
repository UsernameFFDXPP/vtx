#pragma once

#include<iostream>
#include"vtx/alg/MatrixArithm.hpp"

namespace vtx{
    template<typename VType>
    std::ostream &operator<<(std::ostream &os,const Matrix<VType> &mat){
        for(std::size_t row=0;row<mat.rowLength();++row){
            if(row==0) os<<'[';
            else os<<' ';
            for(std::size_t col=0;col<mat.colLength();++col){
                if(col!=mat.colLength()-1) os<<mat(row,col)<<' ';
                else os<<mat(row,col);
            }
            if(row==mat.rowLength()-1) os<<']';
            os<<'\n';
        }
        return os;
    }

    template<typename VType>
    Matrix<VType> operator+(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        return add(lhs,rhs);
    }
    template<typename VType>
    Matrix<VType> &operator+=(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        return add_(lhs,rhs);
    }

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &mat){
        return neg(mat);
    }

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        return sub(lhs,rhs);
    }
    template<typename VType>
    Matrix<VType> &operator-=(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        return sub_(lhs,rhs);
    }

    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,const VType &arg){
        return ewiseMul(lhs,arg);
    }
    template<typename VType>
    Matrix<VType> &operator*=(Matrix<VType> &lhs,const VType &arg){
        return ewiseMul_(lhs,arg);
    }

    template<typename VType>
    Matrix<VType> operator*(const VType &arg,const Matrix<VType> &rhs){
        return ewiseMul(arg,rhs);
    }

    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        return matMul(lhs,rhs);
    }

    template<typename VType>
    Matrix<VType> operator/(const Matrix<VType> &lhs,const VType &arg){
        return ewiseDiv(lhs,arg);
    }
    template<typename VType>
    Matrix<VType> &operator/=(Matrix<VType> &lhs,const VType &arg){
        return ewiseDiv_(lhs,arg);
    }

    template<typename VType>
    Matrix<VType> operator%(const Matrix<VType> &lhs,const VType &arg){
        return ewiseMod(lhs,arg);
    }
    template<typename VType>
    Matrix<VType> &operator%=(Matrix<VType> &lhs,const VType &arg){
        return ewiseMod_(lhs,arg);
    }
    
}