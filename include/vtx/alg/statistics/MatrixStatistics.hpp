#pragma once

#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/View.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Map.hpp"
#include"vtx/alg/statistics/Statistics.hpp"

namespace vtx{
    /*Covariance*/
    template<typename VType>
    Matrix<VType> covariance(const Matrix<VType> &mat,Axis axis=Axis::None){
        if(axis==Axis::Row){
            Matrix<VType> rsl=matMul(center(mat,axis),transpose(center(mat,axis)));
            return rsl/static_cast<VType>(mat.colLength()-1);
        }else if(axis==Axis::Col){
            Matrix<VType> rsl=matMul(transpose(center(mat,axis)),center(mat,axis));
            return rsl/static_cast<VType>(mat.rowLength()-1);
        }else /*Axis Error*/;
        return Matrix<VType>{};
    }
    /*Correlation*/
    template<typename VType>
    Matrix<VType> correlation(const Matrix<VType> &mat,Axis axis=Axis::None){
        if(axis==Axis::Row){
            Matrix<VType>rsl=matMul(sampleStandardize(mat,axis),transpose(sampleStandardize(mat,axis)));
            return rsl/static_cast<VType>(mat.colLength()-1);
        }else if(axis==Axis::Col){
            Matrix<VType>rsl=matMul(transpose(sampleStandardize(mat,axis)),sampleStandardize(mat,axis));
            return rsl/static_cast<VType>(mat.rowLength()-1);
        }else /*Axis Error*/;
        return Matrix<VType>{};
    }
    /*Mean*/
    template<typename VType>
    Matrix<VType> mean(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
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
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
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
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
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
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
        else /*Axis Error*/;
        map::mapReduction(rsl,OprStatistics::Median,mat,axis);
        return rsl;
    }
    /*Center*/
    template<typename VType>
    Matrix<VType> center(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::Sub,mat,mean(mat,axis));
        return rsl;
    }
    /*Standardize*/
    template<typename VType>
    Matrix<VType> standardize(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        Matrix<VType> var=variance(mat,axis);
        for(std::size_t i=0;i<var.size();++i) var(i)=std::sqrt(var(i));
        map::mapBroadcastEwise(rsl,OprArithm::EwiseDiv,center(mat,axis),var);
        return rsl;
    }
    /*SampleStandardize*/
    template<typename VType>
    Matrix<VType> sampleStandardize(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        Matrix<VType> var=sampleVariance(mat,axis);
        for(std::size_t i=0;i<var.size();++i) var(i)=std::sqrt(var(i));
        map::mapBroadcastEwise(rsl,OprArithm::EwiseDiv,center(mat,axis),var);
        return rsl;
    }
    /*Quantile*/
    template<typename VType>
    Matrix<VType> quantile(const Matrix<VType> &mat,Axis axis=Axis::None,double q=0){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else if(axis==Axis::None) rsl=Matrix<VType>(1,1);
        else /*Axis Error*/;
        map::mapQuantile(rsl,OprStatistics::Quantile,mat,axis,q);
        return rsl;
    }
}//namespace vtx