#pragma once

#include"vtx/alg/MatrixArithm.hpp"

namespace vtx{
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