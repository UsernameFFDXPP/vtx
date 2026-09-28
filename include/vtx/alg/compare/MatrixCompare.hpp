#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/alg/Map.hpp"
#include"vtx/alg/arithm/Arithm.hpp"

namespace vtx{
    /*Equal*/
    template<typename VType>
    Matrix<bool> equal(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::Equal,lhs,rhs);
        return rsl;
    }
    /*Greater*/
    template<typename VType>
    Matrix<bool> graeter(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::Greater,lhs,rhs);
        return rsl;
    }
    /*GraeterEqual*/
    template<typename VType>
    Matrix<bool> greaterEqual(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::GreaterEqual,lhs,rhs);
        return rsl;
    }
    /*Less*/
    template<typename VType>
    Matrix<bool> less(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::Less,lhs,rhs);
        return rsl;
    }
    /*LessEqual*/
    template<typename VType>
    Matrix<bool> lessEqual(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::LessEqual,lhs,rhs);
        return rsl;
    }
    /*NotEqual*/
    template<typename VType>
    Matrix<bool> notEqual(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<bool> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprCompare::NotEqual,lhs,rhs);
        return rsl;
    }
}