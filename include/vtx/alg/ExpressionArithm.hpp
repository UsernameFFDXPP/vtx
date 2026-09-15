#pragma once

#include"vtx/core/Expression.hpp"
#include"vtx/core/Operation.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Expression<VType> neg(const Expression<VType> &view){
        return Expression(Operation::Neg,view);
    }
    /*EwiseInv*/
    template<typename VType>
    Expression<VType> ewiseInv(const Expression<VType> &view){
        return Expression(Operation::EwiseInv,view);
    }
    /*EwiseMul*/
    template<typename VType>
    Expression<VType> ewiseMul(const Expression<VType> &view,const VType &arg){
        return Expression(Operation::EwiseMul,view,arg);
    }
    /*EwiseDiv*/
    template<typename VType>
    Expression<VType> ewiseDiv(const Expression<VType> &view,const VType &arg){
        return Expression(Operation::EwiseDiv,view,arg);
    }
    /*EwiseMod*/
    template<typename VType>
    Expression<VType> ewiseMod(const Expression<VType> &view,const VType &arg){
        return Expression(Operation::EwiseMod,view,arg);
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
}