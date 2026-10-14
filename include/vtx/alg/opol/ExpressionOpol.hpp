#pragma once

#include"vtx/alg/arithm/ExpressionArithm.hpp"
#include"vtx/alg/compare/ExpressionCompare.hpp"

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
        return scalarMul(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator*=(Expression<VType> &lhs,const VType &arg){
        return scalarMul_(lhs,arg);
    }

    template<typename VType>
    Expression<VType> operator*(const VType &arg,const Expression<VType> &rhs){
        return scalarMul(arg,rhs);
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
        return scalarDiv(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator/=(Expression<VType> &lhs,const VType &arg){
        return scalarDiv_(lhs,arg);
    }

    template<typename VType>
    Expression<VType> operator%(const Expression<VType> &lhs,const VType &arg){
        return scalarMod(lhs,arg);
    }
    template<typename VType>
    Expression<VType> &operator%=(Expression<VType> &lhs,const Expression<VType> &arg){
        return scalarMod_(lhs,arg);
    }

    template<typename VType>
    Expression<bool> operator==(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return equal(lhs,rhs);
    }
    template<typename VType>
    Expression<bool> operator>(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return greater(lhs,rhs);
    }
    template<typename VType>
    Expression<bool> operator>=(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return greaterEqual(lhs,rhs);
    }
    template<typename VType>
    Expression<bool> operator<(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return less(lhs,rhs);
    }
    template<typename VType>
    Expression<bool> operator<=(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return lessEqual(lhs,rhs);
    }
    template<typename VType>
    Expression<bool> operator!=(const Expression<VType> &lhs,const Expression<VType> &rhs){
        return notEqual(lhs,rhs);
    }
}