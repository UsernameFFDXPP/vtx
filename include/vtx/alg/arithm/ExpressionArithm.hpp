#pragma once

#include"vtx/alg/Expression.hpp"
#include"vtx/alg/Operator.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Expression<VType> neg(const Expression<VType> &expr){
        return Expression(OprArithm::Neg,expr);
    }
    /*EwiseInv*/
    template<typename VType>
    Expression<VType> ewiseInv(const Expression<VType> &expr){
        return Expression(OprArithm::EwiseInv,expr);
    }
    /*EwiseMul*/
    template<typename VType>
    Expression<VType> ewiseMul(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseMul,expr,arg);
    }
    /*EwiseDiv*/
    template<typename VType>
    Expression<VType> ewiseDiv(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseDiv,expr,arg);
    }
    /*EwiseMod*/
    template<typename VType>
    Expression<VType> ewiseMod(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseMod,expr,arg);
    }
    /*Add*/
    template<typename VType>
    Expression<VType> add(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(OprArithm::Add,lhs,rhs);
    }
    /*Sub*/
    template<typename VType>
    Expression<VType> sub(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(OprArithm::Sub,lhs,rhs);
    }
    /*MatMul*/
    template<typename VType>
    Expression<VType> matMul(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(OprArithm::MatMul,lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &matMul_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression(OprArithm::MatMul,lhs,rhs);
        return lhs;
    }
}