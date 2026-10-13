#pragma once

#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<bool> equal(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::Equal,lexpr,rexpr);
    }

    template<typename VType>
    Expression<bool> greater(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::Greater,lexpr,rexpr);
    }

    template<typename VType>
    Expression<bool> greaterEqual(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::GreaterEqual,lexpr,rexpr);
    }

    template<typename VType>
    Expression<bool> less(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::Less,lexpr,rexpr);
    }

    template<typename VType>
    Expression<bool> lessEqual(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::LessEqual,lexpr,rexpr);
    }

    template<typename VType>
    Expression<bool> notEqual(const Expression<VType> &lexpr,const Expression<VType> &rexpr){
        return Expression<bool>(OprCompare::NotEqual,lexpr,rexpr);
    }
}//namespace vtx