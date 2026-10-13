#pragma once

#include<functional>

#include"vtx/alg/Expression.hpp"
#include"vtx/alg/Operator.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Expression<VType> neg(const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprArithm::Neg),expr);
    }
    template<typename VType>
    Expression<VType> &neg_(Expression<VType> &expr){
        expr=Expression<VType>(static_cast<Operator>(OprArithm::Neg),expr);
        return expr;
    }
    /*EwiseInv*/
    template<typename VType>
    Expression<VType> ewiseInv(const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseInv),expr);
    }
    template<typename VType>
    Expression<VType> &ewiseInv_(Expression<VType> &expr){
        expr=Expression<VType>(static_cast<Operator>(OprArithm::EwiseInv),expr);
        return expr;
    }
    /*EwiseMul*/
    template<typename VType>
    Expression<VType> ewiseMul(const Expression<VType> &expr,const VType &arg){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseMul),expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseMul_(Expression<VType> &expr,const VType &arg){
        expr=Expression<VType>(static_cast<Operator>(OprArithm::EwiseMul),expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseMul(const VType &arg,const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseMul),arg,expr);
    }
    /*EwiseDiv*/
    template<typename VType>
    Expression<VType> ewiseDiv(const Expression<VType> &expr,const VType &arg){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseDiv),expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseDiv_(Expression<VType> &expr,const VType &arg){
        expr=Expression<VType>(static_cast<Operator>(OprArithm::EwiseDiv),expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseDiv(const VType &arg,const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseDiv),arg,expr);
    }
    /*EwiseMod*/
    template<typename VType>
    Expression<VType> ewiseMod(const Expression<VType> &expr,const VType &arg){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseMod),expr,arg);
    }
    template<typename VType>
    Expression<VType> &ewiseMod_(Expression<VType> &expr,const VType &arg){
        expr=Expression<VType>(static_cast<Operator>(OprArithm::EwiseMod),expr,arg);
        return expr;
    }
    template<typename VType>
    Expression<VType> ewiseMod(const VType &arg,const Expression<VType> &expr){
        return Expression<VType>(static_cast<Operator>(OprArithm::EwiseMod),arg,expr);
    }
    /*Add*/
    template<typename VType>
    Expression<VType> add(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression<VType>(static_cast<Operator>(OprArithm::Add),lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &add_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression<VType>(static_cast<Operator>(OprArithm::Add),lhs,rhs);
        return lhs;
    }
    /*Sub*/
    template<typename VType>
    Expression<VType> sub(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression<VType>(static_cast<Operator>(OprArithm::Sub),lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &sub_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression<VType>(static_cast<Operator>(OprArithm::Sub),lhs,rhs);
        return lhs;
    }
    /*MatMul*/
    template<typename VType>
    Expression<VType> matMul(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return Expression<VType>(static_cast<Operator>(OprArithm::MatMul),lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &matMul_(Expression<VType> &lhs,const Expression<VType> &rhs){
        lhs=Expression<VType>(static_cast<Operator>(OprArithm::MatMul),lhs,rhs);
        return lhs;
    }
    /*MatInv*/
    /*MatDiv*/
    /*EwiseUnaryFunc*/
    template<typename VTypeI,typename VTypeO>
    Expression<VTypeO> ewiseUnaryFunc(std::function<VTypeO(VTypeI)> func,const Expression<VTypeI> &expr){
        return Expression<VTypeO>(static_cast<Operator>(OprArithm::EwiseUnaryFunc),func,expr);
    }
    /*EwiseBinaryFunc*/
    template<typename VTypeI,typename VTypeO>
    Expression<VTypeO> ewiseBinaryFunc(std::function<VTypeO(VTypeI,VTypeI)> func,const Expression<VTypeI> &lexpr,const Expression<VTypeI> &rexpr){
        return Expression<VTypeO>(static_cast<Operator>(OprArithm::EwiseBinaryFunc),func,lexpr,rexpr);
    }
}