#pragma once

#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/View.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Map.hpp"
#include"vtx/alg/reduction/Reduction.hpp"

namespace vtx{
    /*Sum*/
    template<typename VType>
    Matrix<VType> sum(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::mapReduction(rsl,Operator::Sum,mat,axis);
        return rsl;
    }
    /*Max*/
    template<typename VType>
    Matrix<VType> max(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::mapReduction(rsl,Operator::Max,mat,axis);
        return rsl;
    }
    /*Min*/
    template<typename VType>
    Matrix<VType> min(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::mapReduction(rsl,Operator::Min,mat,axis);
        return rsl;
    }
    /*ArgMax*/
    template<typename VType>
    Matrix<std::size_t> argmax(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) Matrix<std::size_t> rsl(mat.rowLength(),1);
        else if(axis==Axis::Col) Matrix<std::size_t> rsl(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::mapArgReduction(rsl,Operator::ArgMax,mat,axis);
        return rsl;
    }
    /*ArgMin*/
    template<typename VType>
    Matrix<std::size_t> argmin(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) Matrix<std::size_t> rsl(mat.rowLength(),1);
        else if(axis==Axis::Col) Matrix<std::size_t> rsl(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::mapArgReduction(rsl,Operator::ArgMin,mat,axis);
        return rsl;
    }
}//namespace vtx