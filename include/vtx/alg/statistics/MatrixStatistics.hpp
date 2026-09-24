#pragma once

#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/View.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Map.hpp"
#include"vtx/alg/statistics/Statistics.hpp"

namespace vtx{
    /*Mean*/
    template<typename VType>
    Matrix<VType> mean(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        map::mapReduction(rsl,OprStatistics::Mean,mat,axis);
        return rsl;
    }
    /*Variance*/
    template<typename VType>
    Matrix<VType> variance(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        map::mapReduction(rsl,OprStatistics::Variance,mat,axis);
        return rsl;
    }
    /*SampleVariance*/
    template<typename VType>
    Matrix<VType> sampleVariance(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        map::mapReduction(rsl,OprStatistics::SampleVariance,mat,axis);
        return rsl;
    }
    /*Median*/
    template<typename VType>
    Matrix<VType> median(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        map::mapReduction(rsl,OprStatistics::Median,mat,axis);
        return rsl;
    }
    /*Covariance*/
    template<typename VType>
    Matrix<VType> covariance(const Matrix<VType> &mat,Axis axis=Axis::None);
    /*Correlation*/
    template<typename VType>
    Matrix<VType> correlation(const Matrix<VType> &mat,Axis axis=Axis::None);
    /*Quantile*/
    template<typename VType>
    Matrix<VType> quantile(const Matrix<VType> &mat,Axis axis=Axis::None);
}//namespace vtx