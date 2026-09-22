#pragma once

#include"vtx/alg/Expression.hpp"
#include"vtx/alg/Operation.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Expression<VType> neg(const Expression<VType> &expr){
        return Expression(Operation::Neg,expr);
    }
    /*EwiseInv*/
    template<typename VType>
    Expression<VType> ewiseInv(const Expression<VType> &expr){
        return Expression(Operation::EwiseInv,expr);
    }
    /*EwiseMul*/
    template<typename VType>
    Expression<VType> ewiseMul(const Expression<VType> &expr,const VType &arg){
        return Expression(Operation::EwiseMul,expr,arg);
    }
    /*EwiseDiv*/
    template<typename VType>
    Expression<VType> ewiseDiv(const Expression<VType> &expr,const VType &arg){
        return Expression(Operation::EwiseDiv,expr,arg);
    }
    /*EwiseMod*/
    template<typename VType>
    Expression<VType> ewiseMod(const Expression<VType> &expr,const VType &arg){
        return Expression(Operation::EwiseMod,expr,arg);
    }
    /*Add*/
    template<typename VType>
    Expression<VType> add(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(Operation::Add,lhs,rhs);
    }
    /*Sub*/
    template<typename VType>
    Expression<VType> sub(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(Operation::Sub,lhs,rhs);
    }
    /*MatMul*/
    template<typename VType>
    Expression<VType> matMul(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(Operation::MatMul,lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &matMul_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression(Operation::MatMul,lhs,rhs);
        return lhs;
    }
}