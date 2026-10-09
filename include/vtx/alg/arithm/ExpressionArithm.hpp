#pragma once

#include"vtx/alg/Expression.hpp"
#include"vtx/alg/Operator.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Expression<VType> neg(const Expression<VType> &expr){
        return Expression(OprArithm::Neg,expr);
    }
    template<typename VType>
    Expression<VType> &neg_(Expression<VType> &expr){
        expr=Expression(OprArithm::Neg,expr);
        return expr;
    }
    /*EwiseInv*/
    template<typename VType>
    Expression<VType> ewiseInv(const Expression<VType> &expr){
        return Expression(OprArithm::EwiseInv,expr);
    }
    template<typename VType>
    Expression<VType> &ewiseInv_(Expression<VType> &expr){
        expr=Expression(OprArithm::EwiseInv,expr);
        return expr;
    }
    /*EwiseMul*/
    template<typename VType>
    Expression<VType> ewiseMul(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseMul,expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseMul_(Expression<VType> &expr,const VType &arg){
        expr=Expression(OprArithm::EwiseMul,expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseMul(const VType &arg,const Expression<VType> &expr){
        return Expression(OprArithm::EwiseMul,arg,expr);
    }
    /*EwiseDiv*/
    template<typename VType>
    Expression<VType> ewiseDiv(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseDiv,expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseDiv_(Expression<VType> &expr,const VType &arg){
        expr=Expression(OprArithm::EwiseDiv,expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseDiv(const VType &arg,const Expression<VType> &expr){
        return Expression(OprArithm::EwiseDiv,arg,expr);
    }
    /*EwiseMod*/
    template<typename VType>
    Expression<VType> ewiseMod(const Expression<VType> &expr,const VType &arg){
        return Expression(OprArithm::EwiseMod,expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseMod_(Expression<VType> &expr,const VType &arg){
        expr=Expression(OprArithm::EwiseMod,expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseMod(const VType &arg,const Expression<VType> &expr){
        return Expression(OprArithm::EwiseMod,arg,expr);
    }
    /*Add*/
    template<typename VType>
    Expression<VType> add(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(OprArithm::Add,lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &add_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression(OprArithm::Add,lhs,rhs);
        return lhs;
    }
    /*Sub*/
    template<typename VType>
    Expression<VType> sub(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression(OprArithm::Sub,lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &sub_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression(OprArithm::Sub,lhs,rhs);
        return lhs;
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