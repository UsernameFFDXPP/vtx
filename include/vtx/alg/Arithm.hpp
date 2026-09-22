#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<type_traits>
#include<vector>

#include"vtx/core/Operation.hpp"

namespace vtx{
    namespace type_opr_traits{
        template<typename T,typename=void>
        struct isNegAble:std::false_type{};
        template<typename T>
        struct isNegAble<T,std::void_t<decltype(-std::declval<T>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isAddAble:std::false_type{};
        template<typename L,typename R>
        struct isAddAble<L,R,std::void_t<decltype(std::declval<L>()+std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isSubAble:std::false_type{};
        template<typename L,typename R>
        struct isSubAble<L,R,std::void_t<decltype(std::declval<L>()-std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isMulAble:std::false_type{};
        template<typename L,typename R>
        struct isMulAble<L,R,std::void_t<decltype(std::declval<L>()*std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isDivAble:std::false_type{};
        template<typename L,typename R>
        struct isDivAble<L,R,std::void_t<decltype(std::declval<L>()/std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isModAble:std::false_type{};
        template<typename L,typename R>
        struct isModAble<L,R,std::void_t<decltype(std::declval<L>()%std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isEqualAble:std::false_type{};
        template<typename L,typename R>
        struct isEqualAble<L,R,std::void_t<decltype(std::declval<L>()==std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isGreaterAble:std::false_type{};
        template<typename L,typename R>
        struct isGreaterAble<L,R,std::void_t<decltype(std::declval<L>()>std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isGreaterEqualAble:std::false_type{};
        template<typename L,typename R>
        struct isGreaterEqualAble<L,R,std::void_t<decltype(std::declval<L>()>=std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isLessAble:std::false_type{};
        template<typename L,typename R>
        struct isLessAble<L,R,std::void_t<decltype(std::declval<L>()<std::declval<R>())>>:std::true_type{};

        template<typename L,typename R,typename=void>
        struct isLessEqualAble:std::false_type{};
        template<typename L,typename R>
        struct isLessEqualAble<L,R,std::void_t<decltype(std::declval<L>()<=std::declval<R>())>>:std::true_type{};
    }//namespace type_opr_traits

    /*Neg*/
    template<typename VType>
    auto arithmNeg(const VType &val)->std::enable_if_t<
        type_opr_traits::isNegAble<VType>::value,VType
    >{
        return -val;
    }
    /*Inv*/
    template<typename VType>
    auto arithmEwiseInv(const VType &val)->std::enable_if_t<
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        return VType{}/val;
    }
    /*EwiseMul*/
    template<typename VType>
    auto arithmEwiseMul(const VType &rhs,const VType &lhs)->std::enable_if_t<
        type_opr_traits::isMulAble<VType,VType>::value,VType
    >{
        return rhs*lhs;
    }
    /*EwiseDiv*/
    template<typename VType>
    auto arithmEwiseDiv(const VType &rhs,const VType &lhs)->std::enable_if_t<
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        return rhs/lhs;
    }
    /*EwiseMod*/
    template<typename VType>
    auto arithmEwiseMod(const VType &rhs,const VType &lhs)->std::enable_if_t<
        type_opr_traits::isModAble<VType,VType>::value,VType
    >{
        return rhs%lhs;
    }
    /*Add*/
    template<typename VType>
    auto arithmAdd(const VType &rhs,const VType &lhs)->std::enable_if_t<
        type_opr_traits::isAddAble<VType,VType>::value,VType
    >{
        return rhs+lhs;
    }
    /*Sub*/
    template<typename VType>
    auto arithmSub(const VType &rhs,const VType &lhs)->std::enable_if_t<
        type_opr_traits::isSubAble<VType,VType>::value,VType
    >{
        return rhs-lhs;
    }
    /*MatMul*/
    template<typename Lhs,typename Rhs,typename VType=typename Lhs::value_type>
    auto arithmMatMul(const Lhs &lhs,const Rhs &rhs)->std::enable_if_t<
        type_opr_traits::isMulAble<VType,VType>::value,VType
    >{
        VType rsl{};
        for(std::size_t idx=0;idx<lhs.size();++idx){
            rsl+=lhs(idx)*rhs(idx);
        }
        return rsl;
    }
    /*Sum*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmSum(const Line &val)->std::enable_if_t<
        type_opr_traits::isAddAble<VType,VType>::value,VType
    >{
        VType rsl{};
        for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
        return rsl;
    }
    /*Max,ArgMax*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMax(const Line &val)->std::enable_if_t<
        type_opr_traits::isGreaterAble<VType,VType>::value,VType
    >{
        VType rsl=val(0);
        for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i);
        return rsl;
    }
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmArgMax(const Line &val)->std::enable_if_t<
        type_opr_traits::isGreaterAble<VType,VType>::value,std::size_t
    >{
        auto rsl=val(0);std::size_t tIdx=0;
        for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i),tIdx=i;
        return tIdx;
    }
    /*Min,ArgMin*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMin(const Line &val)->std::enable_if_t<
        type_opr_traits::isLessAble<VType,VType>::value,VType
    >{
        VType rsl=val(0);
        for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i);
        return rsl;
    }
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmArgMin(const Line &val)->std::enable_if_t<
        type_opr_traits::isLessAble<VType,VType>::value,std::size_t
    >{
        auto rsl=val(0);std::size_t tIdx=0;
        for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i),tIdx=i;
        return tIdx;
    }
    /*Mean*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMean(const Line &val)->std::enable_if_t<
        type_opr_traits::isAddAble<VType,VType>::value&&
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        VType rsl{};
        for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
        return rsl/static_cast<VType>(val.size());
    }
    /*Variance*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmVariance(const Line &val)->std::enable_if_t<
        type_opr_traits::isAddAble<VType,VType>::value&&
        type_opr_traits::isModAble<VType,VType>::value&&
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        VType mean{},m2{};
        for(std::size_t i=0;i<val.size();++i){
            VType d1=val(i)-mean;
            mean+=d1/static_cast<VType>(i+1);
            VType d2=val(i)-mean;
            m2+=d1*d2;
        }
        return m2/static_cast<VType>(val.size());
    }
    /*SampleVariance*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmSampleVariance(const Line &val)->std::enable_if_t<
        type_opr_traits::isAddAble<VType,VType>::value&&
        type_opr_traits::isModAble<VType,VType>::value&&
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        VType mean{},m2{};
        for(std::size_t i=0;i<val.size();++i){
            VType d1=val(i)-mean;
            mean+=d1/static_cast<VType>(i+1);
            VType d2=val(i)-mean;
            m2+=d1*d2;
        }
        return m2/static_cast<VType>(val.size()-1);
    }
    /*Median*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMedian(const Line &val)->std::enable_if_t<
        type_opr_traits::isDivAble<VType,VType>::value,VType
    >{
        std::vector<VType> temp(val.size());
        for(std::size_t i=0;i<val.size();++i) temp[i]=val(i);
        if(val.size()%2==1){
            std::nth_element(temp.begin(),temp.begin()+temp.size()/2,temp.end());
            return temp[temp.size()/2];
        }else{
            std::nth_element(temp.begin(),temp.begin()+temp.size()/2+1,temp.end());
            return (temp[temp.size()/2-1]+temp[temp.size()/2])/static_cast<VType>(2);
        }
    }
}//namespace vtx

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