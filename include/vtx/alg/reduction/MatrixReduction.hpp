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
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
        else /*Axis Error*/;
        map::mapReduction(rsl,OprReduction::Sum,mat,axis);
        return rsl;
    }
    /*Max*/
    template<typename VType>
    Matrix<VType> max(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
        else /*Axis Error*/;
        map::mapReduction(rsl,OprReduction::Max,mat,axis);
        return rsl;
    }
    /*Min*/
    template<typename VType>
    Matrix<VType> min(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
        else /*Axis Error*/;
        map::mapReduction(rsl,OprReduction::Min,mat,axis);
        return rsl;
    }
    /*ArgMax*/
    template<typename VType>
    Matrix<std::size_t> argMax(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<std::size_t> rsl;
        if(axis==Axis::Row) rsl=Matrix<std::size_t>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<std::size_t>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<std::size_t>(1,1);
        else /*Axis Error*/;
        map::mapArgReduction(rsl,OprReduction::ArgMax,mat,axis);
        return rsl;
    }
    /*ArgMin*/
    template<typename VType>
    Matrix<std::size_t> argMin(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<std::size_t> rsl;
        if(axis==Axis::Row) rsl=Matrix<std::size_t>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<std::size_t>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<std::size_t>(1,1);
        else /*Axis Error*/;
        map::mapArgReduction(rsl,OprReduction::ArgMin,mat,axis);
        return rsl;
    }
}//namespace vtx