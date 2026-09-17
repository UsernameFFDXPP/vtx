#pragma once

#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    namespace arithmmap{
        template<typename VType>
        void reductionMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &mat,Axis axis){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VType>> tempView(&mat,Axis::Row,row);
                    rsl(row,0)=reductionArithm(opr,tempView);
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.rowLength();++col){
                    View<Matrix<VType>> tempView(&mat,Axis::Col,col);
                    rsl(0,col)=reductionArithm(opr,tempView);
                }
            }else{
                /*Axis Error*/
            }
        }

        template<typename VType>
        void argReductionMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &mat,Axis axis){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VType>> tempView(&mat,Axis::Row,row);
                    rsl(row,1)=argReductionArithm(opr,tempView);
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.rowLength();++col){
                    View<Matrix<VType>> tempView(&mat,Axis::Col,col);
                    rsl(1,col)=argReductionArithm(opr,tempView);
                }
            }else{
                /*Axis Error*/
            }
        }
    }

    /*Sum*/
    template<typename VType>
    Matrix<VType> sum(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Sum,mat,axis);
        return rsl;
    }
    /*Max*/
    template<typename VType>
    Matrix<VType> max(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Max,mat,axis);
        return rsl;
    }
    /*Min*/
    template<typename VType>
    Matrix<VType> min(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Min,mat,axis);
        return rsl;
    }
    /*ArgMax*/
    template<typename VType>
    Matrix<std::size_t> argmax(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) Matrix<std::size_t> rsl(mat.rowLength(),1);
        else if(axis==Axis::Col) Matrix<std::size_t> rsl(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::argReductionMap(rsl,Operation::ArgMax,mat,axis);
        return rsl;
    }
    /*ArgMin*/
    template<typename VType>
    Matrix<std::size_t> argmin(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) Matrix<std::size_t> rsl(mat.rowLength(),1);
        else if(axis==Axis::Col) Matrix<std::size_t> rsl(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::argReductionMap(rsl,Operation::ArgMin,mat,axis);
        return rsl;
    }
    /*Mean*/
    template<typename VType>
    Matrix<VType> mean(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Mean,mat,axis);
        return rsl;
    }
    /*Variance*/
    template<typename VType>
    Matrix<VType> variance(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Variance,mat,axis);
        return rsl;
    }
    /*SampleVariance*/
    template<typename VType>
    Matrix<VType> sampleVariance(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::SampleVariance,mat,axis);
        return rsl;
    }
    /*Median*/
    template<typename VType>
    Matrix<VType> median(const Matrix<VType> &mat,Axis axis=Axis::None){
        Matrix<VType> rsl;
        if(axis==Axis::Row) rsl=Matrix<VType>(mat.rowLength(),1);
        else if(axis==Axis::Col) rsl=Matrix<VType>(1,mat.colLength());
        else /*Axis Error*/;
        arithmmap::reductionMap(rsl,Operation::Median,mat,axis);
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
}