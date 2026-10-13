#pragma once

#include"vtx/alg/Expression.hpp"
#include"vtx/alg/arithm/ExpressionArithm.hpp"
#include"vtx/alg/layout/ExpressionLayout.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType> covariance(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::Covariance,expr,axis);
    }

    template<typename VType>
    Expression<VType> correlation(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::Correlation,expr,axis);
    }

    template<typename VType>
    Expression<VType> mean(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::Mean,expr,axis);
    }

    template<typename VType>
    Expression<VType> variance(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::Variance,expr,axis);
    }

    template<typename VType>
    Expression<VType> sampleVariance(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::SampleVariance,expr,axis);
    }

    template<typename VType>
    Expression<VType> median(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprStatistics::Median,expr,axis);
    }

    template<typename VType>
    Expression<VType> center(const Expression<VType> &expr,Axis axis){
        //return Expression<VType>(OprStatistics::Center,expr,axis);
        auto meanExpr=broadcast(mean(expr,axis),expr.rowLength(),expr.colLength());
        return sub(expr,meanExpr);
    }

    template<typename VType>
    Expression<VType> standardize(const Expression<VType> &expr,Axis axis){
        //return Expression<VType>(OprStatistics::Standardize,expr,axis);
        auto valExpr=ewiseUnaryFunc<VType,VType>([](VType val){return std::sqrt(val);},variance(expr,axis));
        return ewiseDiv(center(expr,axis),broadcast(valExpr,expr.rowLength(),expr.colLength()));
    }

    template<typename VType>
    Expression<VType> sampleStandardize(const Expression<VType> &expr,Axis axis){
        //return Expression<VType>(OprStatistics::SampleStandardize,expr,axis);
        auto valExpr=ewiseUnaryFunc<VType,VType>([](VType val){return std::sqrt(val);},sampleVariance(expr,axis));
        return ewiseDiv(center(expr,axis),broadcast(valExpr,expr.rowLength(),expr.colLength()));
    }

    template<typename VType>
    Expression<VType> quantile(const Expression<VType> &expr,Axis axis,double arg){
        return Expression<VType>(OprStatistics::Quantile,expr,axis,arg);
    }
}//namespace vtx