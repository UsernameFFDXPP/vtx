#pragma once

#include<cstddef>

#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType> transpose(const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprLayout::Transpose),expr);
    }

    template<typename VType>
    Expression<VType> flip(const Expression<VType> &expr,Axis axis){
        return Expression<VType>(static_cast<Operator>(OprLayout::Flip),expr,axis);
    }
    
    template<typename VType>
    Expression<VType> reshape(const Expression<VType> &expr,std::size_t idx1,std::size_t idx2){
        return Expression<VType>(static_cast<Operator>(OprLayout::Reshape),expr,idx1,idx2);
    }

    template<typename VType>
    Expression<VType> resize(const Expression<VType> &expr,std::size_t idx1,std::size_t idx2){
        return Expression<VType>(static_cast<Operator>(OprLayout::Resize),expr,idx1,idx2);
    }

    template<typename VType>
    Expression<VType> insert(const Expression<VType> &expr,Axis axis,std::size_t idx){
        return Expression<VType>(static_cast<Operator>(OprLayout::Insert),expr,axis,idx);
    }

    template<typename VType>
    Expression<VType> drop(const Expression<VType> &expr,Axis axis,std::size_t idx){
        return Expression<VType>(static_cast<Operator>(OprLayout::Drop),expr,axis,idx);
    }

    template<typename VType>
    Expression<VType> swap(const Expression<VType> &expr,Axis axis,std::size_t idx1,std::size_t idx2){
        return Expression<VType>(static_cast<Operator>(OprLayout::Swap),expr,axis,idx1,idx2);
    }

    template<typename VType>
    Expression<VType> slice(const Expression<VType> &expr,Axis axis,std::size_t idx1,std::size_t idx2){
        return Expression<VType>(static_cast<Operator>(OprLayout::Slice),expr,axis,idx1,idx2);
    }

    template<typename VType>
    Expression<VType> concat(const Expression<VType> &lexpr,const Expression<VType> &rexpr,Axis axis){
        return Expression<VType>(static_cast<Operator>(OprLayout::Concat),lexpr,rexpr,axis);
    }
}//namespace vtx