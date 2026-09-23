#pragma once

#include<type_traits>
#include<variant>

#include"vtx/alg/Operator.hpp"

namespace vtx{
    namespace opr_traits{
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

        template<typename L,typename R,typename=void>
        struct isNotEqualAble:std::false_type{};
        template<typename L,typename R>
        struct isNotEqualAble<L,R,std::void_t<decltype(std::declval<L>()!=std::declval<R>())>>:std::true_type{};

        template<typename VType,typename OprType,OprType Opr>
        struct OprDemandImpl:std::false_type{};
        template<typename VType,OprDefault Opr>
        struct OprDemandImpl<VType,OprDefault,Opr>:std::bool_constant<
            true
        >{};
        template<typename VType,OprArithm Opr>
        struct OprDemandImpl<VType,OprArithm,Opr>:std::bool_constant<
            Opr==OprArithm::Neg?
                isNegAble<VType>::value
            :Opr==OprArithm::EwiseInv ||
             Opr==OprArithm::EwiseDiv?
                isDivAble<VType,VType>::value
            :Opr==OprArithm::EwiseMul?
                isMulAble<VType,VType>::value
            :Opr==OprArithm::EwiseMod?
                isModAble<VType,VType>::value
            :Opr==OprArithm::Add?
                isAddAble<VType,VType>::value
            :Opr==OprArithm::Sub?
                isSubAble<VType,VType>::value
            :Opr==OprArithm::MatMul?
                isAddAble<VType,VType>::value &&
                isMulAble<VType,VType>::value
            :false
        >{};
        template<typename VType,OprCompare Opr>
        struct OprDemandImpl<VType,OprCompare,Opr>:std::bool_constant<
            Opr==OprCompare::Equal?
                isEqualAble<VType,VType>::value
            :Opr==OprCompare::Greater?
                isGreaterAble<VType,VType>::value
            :Opr==OprCompare::GreaterEqual?
                isGreaterEqualAble<VType,VType>::value
            :Opr==OprCompare::Less?
                isLessAble<VType,VType>::value
            :Opr==OprCompare::LessEqual?
                isLessEqualAble<VType,VType>::value
            :Opr==OprCompare::NotEqual?
                isNotEqualAble<VType,VType>::value
            :false
        >{};
        template<typename VType,OprLayout Opr>
        struct OprDemandImpl<VType,OprLayout,Opr>:std::bool_constant<
            true
        >{};
        template<typename VType,OprReduction Opr>
        struct OprDemandImpl<VType,OprReduction,Opr>:std::bool_constant<
            Opr==OprReduction::Sum?
                isAddAble<VType,VType>::value
            :Opr==OprReduction::Max ||
             Opr==OprReduction::ArgMax?
                isGreaterAble<VType,VType>::value
            :Opr==OprReduction::Min ||
             Opr==OprReduction::ArgMin?
                isLessAble<VType,VType>::value
            :false
        >{};
        template<typename VType,OprStatistics Opr>
        struct OprDemandImpl<VType,OprStatistics,Opr>:std::bool_constant<
            Opr==OprStatistics::Covariance?
                /**/
            :Opr==OprStatistics::Correlation?
                /**/
            :Opr==OprStatistics::Mean ||
                Opr==OprStatistics::Variance ||
                Opr==OprStatistics::SampleVariance?
                isAddAble<VType,VType>::value &&
                isMulAble<VType,VType>::value &&
                isDivAble<VType,VType>::value
            :Opr==OprStatistics::Median?
                isDivAble<VType,VType>::value
            :Opr==OprStatistics::Center?
                /**/
            :Opr==OprStatistics::Standardize?
                /**/
            :Opr==OprStatistics::Quantile?
                /**/
            :false
        >{};

        template<typename VType,auto Opr>
        constexpr bool getOprDemand(){
            using OprType=decltype(Opr);
            return OprDemandImpl<VType,OprType,Opr>::value;
        }
    }//namespace type_opr_traits
}//namespace vtx