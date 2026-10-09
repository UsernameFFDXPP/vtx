#pragma once

#include"vtx/alg/arithm/ExpressionArithm.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType> operator+(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return add(lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &operator+=(Expression<VType> &lhs,const Expression<VType> &rhs){
        return add_(lhs,rhs);
    }

    template<typename VType>
    Expression<VType> operator-(const Expression<VType> &view){
        return neg(view);
    }

    template<typename VType>
    Expression<VType> operator-(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return sub(lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &operator-=(Expression<VType> &lhs,const Expression<VType> &rhs){
        return sub_(lhs,rhs);
    }

    template<typename VType>
    Expression<VType> operator*(const Expression<VType> &lhs,const VType &arg){
        return ewiseMul(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator*=(Expression<VType> &lhs,const VType &arg){
        return ewiseMul_(lhs,arg);
    }

    template<typename VType>
    Expression<VType> operator*(const VType &arg,const Expression<VType> &rhs){
        return ewiseMul(arg,rhs);
    }

    template<typename VType>
    Expression<VType> operator*(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return matMul(lhs,rhs);
    }
    template<typename VType>
    Expression<VType> &operator*=(Expression<VType> &lhs,const Expression<VType> &rhs){
        return matMul_(lhs,rhs);
    }

    template<typename VType>
    Expression<VType> operator/(const Expression<VType> &lhs,const VType &arg){
        return ewiseDiv(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator/=(Expression<VType> &lhs,const VType &arg){
        return ewiseDiv_(lhs,arg);
    }

    template<typename VType>
    Expression<VType> operator%(const Expression<VType> &lhs,const VType &arg){
        return ewiseMod(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator%=(Expression<VType> &lhs,const Expression<VType> &arg){
        return ewiseMod_(lhs,arg);
    }
}