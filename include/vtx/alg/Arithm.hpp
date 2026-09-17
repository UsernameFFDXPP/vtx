#pragma once

#include<algorithm>
#include<vector>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/View.hpp"
#include"vtx/core/Operation.hpp"

namespace vtx{
    template<typename VType>
    VType unaryEwiseArithm(Operation opr,VType val){
        switch(opr){
            case Operation::Neg:
                return -val;
            case Operation::EwiseInv:
                return 1/val;
            default:
                break;
        }
        return VType{};
    }

    template<typename VType>
    VType binaryEwiseArithm(Operation opr,VType lhs,VType rhs){
        switch(opr){
            case Operation::Add:
                return lhs+rhs;
            case Operation::Sub:
                return lhs-rhs;
            case Operation::EwiseMul:
                return lhs*rhs;
            case Operation::EwiseDiv:
                return lhs/rhs;
            case Operation::EwiseMod:
                return lhs%rhs;
            default:
                break;
        }
        return VType{};
    }

    template<typename VType,template<typename> typename Source>
    VType matMulArithm(View<Source<VType>> lhs,View<Source<VType>> rhs){
        VType rsl{};
        for(std::size_t i=0;i<lhs.size();i++){
            rsl+=lhs(i)*rhs(i);
        }
        return rsl;
    }

    template<typename VType,template<typename> typename Source>
    VType reductionArithm(Operation opr,View<Source<VType>> val){
        switch(opr){
            case Operation::Sum:{
                VType rsl{};
                for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
                return rsl;
            }
            case Operation::Max:{
                VType rsl=val(0);
                for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i);
                return rsl;
            }
            case Operation::Min:{
                VType rsl=val(0);
                for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i);
                return rsl;
            }
            case Operation::Mean:{
                VType rsl{};
                for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
                return rsl/static_cast<VType>(val.size());
            }
            case Operation::Variance:{
                VType mean{},m2{};
                for(std::size_t i=0;i<val.size();++i){
                    VType d1=val(i)-mean;
                    mean+=d1/static_cast<VType>(i+1);
                    VType d2=val(i)-mean;
                    m2+=d1*d2;
                }
                return m2/static_cast<VType>(val.size());
            }
            case Operation::SampleVariance:{
                VType mean{},m2{};
                for(std::size_t i=0;i<val.size();++i){
                    VType d1=val(i)-mean;
                    mean+=d1/static_cast<VType>(i+1);
                    VType d2=val(i)-mean;
                    m2+=d1*d2;
                }
                return m2/static_cast<VType>(val.size()-1);
            }
            case Operation::Median:{
                std::vector<VType> temp(val.size());
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
        return VType{};
    }

    template<typename VType,template<typename> typename Source>
    std::size_t argReductionArithm(Operation opr,View<Source<VType>> val){
        switch(opr){
            case Operation::ArgMax:{
                VType rsl=val(0);std::size_t tIdx=0;
                for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i),tIdx=i;
                return tIdx;
            }
            case Operation::ArgMin:{
                VType rsl=val(0);std::size_t tIdx=0;
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