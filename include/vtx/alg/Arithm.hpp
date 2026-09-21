#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<type_traits>
#include<vector>

#include"vtx/core/Operation.hpp"

namespace vtx{
    template<typename VType>
    VType arithmNeg(const VType &val){
        return -val;
    }

    template<typename VType>
    VType arithmEwiseInv(const VType &val){
        return VType{}/val;
    }

    template<typename VType>
    VType arithmEwiseMul(const VType &rhs,const VType &lhs){
        return rhs*lhs;
    }

    template<typename VType>
    VType arithmEwiseDiv(const VType &rhs,const VType &lhs){
        return rhs/lhs;
    }

    template<typename VType>
    VType arithmEwiseMod(const VType &rhs,const VType &lhs){
        return rhs%lhs;
    }

    template<typename VType>
    VType arithmAdd(const VType &rhs,const VType &lhs){
        return rhs+lhs;
    }

    template<typename VType>
    VType arithmSub(const VType &rhs,const VType &lhs){
        return rhs-lhs;
    }

    template<typename Lhs,typename Rhs>
    auto arithmMatMul(const Lhs &lhs,const Rhs &rhs)->typename Lhs::value_type{
        using value_type=typename Lhs::value_type;
        value_type rsl{};
        for(std::size_t idx=0;idx<lhs.size();++idx){
            rsl+=lhs(idx)*rhs(idx);
        }
        return rsl;
    }

    template<typename Line>
    auto arithmReduction(Operation opr,const Line &val)->typename Line::value_type{
        using value_type=typename Line::value_type;
        switch(opr){
            case Operation::Sum:{
                value_type rsl{};
                for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
                return rsl;
            }
            case Operation::Max:{
                value_type rsl=val(0);
                for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i);
                return rsl;
            }
            case Operation::Min:{
                value_type rsl=val(0);
                for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i);
                return rsl;
            }
            case Operation::Mean:{
                value_type rsl{};
                for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
                return rsl/static_cast<value_type>(val.size());
            }
            case Operation::Variance:{
                value_type mean{},m2{};
                for(std::size_t i=0;i<val.size();++i){
                    value_type d1=val(i)-mean;
                    mean+=d1/static_cast<value_type>(i+1);
                    value_type d2=val(i)-mean;
                    m2+=d1*d2;
                }
                return m2/static_cast<value_type>(val.size());
            }
            case Operation::SampleVariance:{
                value_type mean{},m2{};
                for(std::size_t i=0;i<val.size();++i){
                    value_type d1=val(i)-mean;
                    mean+=d1/static_cast<value_type>(i+1);
                    value_type d2=val(i)-mean;
                    m2+=d1*d2;
                }
                return m2/static_cast<value_type>(val.size()-1);
            }
            case Operation::Median:{
                std::vector<value_type> temp(val.size());
                for(std::size_t i=0;i<val.size();++i) temp[i]=val(i);
                if(val.size()%2==1){
                    std::nth_element(temp.begin(),temp.begin()+temp.size()/2,temp.end());
                    return temp[temp.size()/2];
                }else{
                    std::nth_element(temp.begin(),temp.begin()+temp.size()/2+1,temp.end());
                    return (temp[temp.size()/2]+temp[temp.size()/2+1])/2;
                }
            }
            default:{
                /*Operation Error*/
            }
        }
        return value_type{};
    }

    template<typename Line>
    std::size_t arithmArgReduction(Operation opr,const Line &val){
        switch(opr){
            case Operation::ArgMax:{
                auto rsl=val(0);std::size_t tIdx=0;
                for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i),tIdx=i;
                return tIdx;
            }
            case Operation::ArgMin:{
                auto rsl=val(0);std::size_t tIdx=0;
                for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i),tIdx=i;
                return tIdx;
            }
            default:{
                /*Operation Error*/
            }
        }
    }
}

/*
namespace vtx{

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &mat);

    template<typename VType>
    Matrix<VType> transpose(const Matrix<VType> &mat);

    template<typename VType>
    Matrix<VType> inverse(const Matrix<VType> &mat);


    template<typename VType>
    Matrix<VType> operator*(VType lhs,const Matrix<VType> &rhs);
    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,VType rhs);

    template<typename VType>
    Matrix<VType> operator/(const Matrix<VType> &lhs,VType rhs);


    template<typename VType>
    Matrix<VType> operator+(const Matrix<VType> &lhs,const Matrix<VType> &rhs);

    template<typename VType>
    Matrix<VType> operator-(const Matrix<VType> &lhs,const Matrix<VType> &rhs);

    template<typename VType>
    Matrix<VType> operator*(const Matrix<VType> &lhs,const Matrix<VType> &rhs);


    template<typename VType>
    VType trace(const Matrix<VType> &mat);

    template<typename VType>
    VType rank(const Matrix<VType> &mat);

    template<typename VType>
    VType determinant(const Matrix<VType> &mat);
}
*/