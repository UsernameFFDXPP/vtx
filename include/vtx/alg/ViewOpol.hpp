#pragma once

#include"vtx/alg/ViewArithm.hpp"

namespace vtx{
    template<typename VType>
    View<VType> operator+(const View<VType> &lhs,const View<VType> &rhs){
        return add(lhs,rhs);
    }
    template<typename VType>
    View<VType> &operator+=(View<VType> &lhs,const View<VType> &rhs){
        lhs=add(lhs,rhs);
        return lhs;
    }

    template<typename VType>
    View<VType> operator-(const View<VType> &view){
        return neg(view);
    }

    template<typename VType>
    View<VType> operator-(const View<VType> &lhs,const View<VType> &rhs){
        return sub(lhs,rhs);
    }
    template<typename VType>
    View<VType> &operator-=(View<VType> &lhs,const View<VType> &rhs){
        lhs=sub(lhs,rhs);
        return lhs;
    }

    template<typename VType>
    View<VType> operator*(const View<VType> &lhs,const VType &arg){
        return ewiseMul(lhs,arg);
    }
    template<typename VType>
    View<VType> &operator*=(View<VType> &lhs,const VType &arg){
        lhs=ewiseMul(lhs,arg);
        return lhs;
    }
    template<typename VType>
    View<VType> operator*(const VType &arg,const View<VType> &rhs){
        return ewiseMul(arg,rhs);
    }

    template<typename VType>
    View<VType> operator/(const View<VType> &lhs,const VType &arg){
        return ewiseDiv(lhs,arg);
    }
    template<typename VType>
    View<VType> &operator/=(View<VType> &lhs,const VType &arg){
        lhs=ewiseDiv(lhs,arg);
        return lhs;
    }

    template<typename VType>
    View<VType> operator%(const View<VType> &lhs,const VType &arg){
        return ewiseMod(lhs,arg);
    }
    template<typename VType>
    View<VType> &operator%=(View<VType> &lhs,const View<VType> &arg){
        lhs=ewiseMod(lhs,arg);
        return lhs;
    }
}