#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Operation.hpp"

namespace vtx{
    template<typename VType>
    VType unaryEwiseArithm(Operation opr,VType val){
        switch(opr){
            case Operation::Neg:
                return -val;
            case Operation::EwiseInv:
                return 1/val;
            default:
                break;
        }
        return VType{};
    }

    template<typename VType>
    VType binaryEwiseArithm(Operation opr,VType lhs,VType rhs){
        switch(opr){
            case Operation::Add:
                return lhs+rhs;
            case Operation::Sub:
                return lhs-rhs;
            case Operation::EwiseMul:
                return lhs*rhs;
            case Operation::EwiseDiv:
                return lhs/rhs;
            case Operation::EwiseMod:
                return lhs%rhs;
            default:
                break;
        }
        return VType{};
    }
}


/*
namespace vtx{

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &mat);

    template<typename VType>
    Matrix<VType> transpose(const Matrix<VType> &mat);

    template<typename VType>
    Matrix<VType> inverse(const Matrix<VType> &mat);


    template<typename VType>
    Matrix<VType> operator*(VType lhs,const Matrix<VType> &rhs);
    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,VType rhs);

    template<typename VType>
    Matrix<VType> operator/(const Matrix<VType> &lhs,VType rhs);


    template<typename VType>
    Matrix<VType> operator+(const Matrix<VType> &lhs,const Matrix<VType> &rhs);

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &lhs,const Matrix<VType> &rhs);

    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,const Matrix<VType> &rhs);


    template<typename VType>
    VType trace(const Matrix<VType> &mat);

    template<typename VType>
    VType rank(const Matrix<VType> &mat);

    template<typename VType>
    VType determinant(const Matrix<VType> &mat);
}
*/