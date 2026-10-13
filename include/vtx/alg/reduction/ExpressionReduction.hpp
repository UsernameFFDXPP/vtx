#pragma once

#include<cstddef>

#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType> sum(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprReduction::Sum,expr,axis);
    }

    template<typename VType>
    Expression<VType> max(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprReduction::Max,expr,axis);
    }

    template<typename VType>
    Expression<VType> min(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(OprReduction::Min,expr,axis);
    }

    template<typename VType>
    Expression<std::size_t> argMax(const Expression<VType> &expr,Axis axis){
        return Expression<std::size_t>(OprReduction::ArgMax,expr,axis);
    }

    template<typename VType>
    Expression<std::size_t> argMin(const Expression<VType> &expr,Axis axis){
        return Expression<std::size_t>(OprReduction::ArgMin,expr,axis);
    }
}//namespace vtx