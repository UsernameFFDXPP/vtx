#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<vector>

#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    auto arithmNeg(const VType &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Neg>(),VType
    >{
        return -val;
    }
    /*Inv*/
    template<typename VType>
    auto arithmEwiseInv(const VType &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseInv>(),VType
    >{
        return VType{}/val;
    }
    /*EwiseMul*/
    template<typename VType>
    auto arithmEwiseMul(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseMul>(),VType
    >{
        return rhs*lhs;
    }
    /*EwiseDiv*/
    template<typename VType>
    auto arithmEwiseDiv(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>(),VType
    >{
        return rhs/lhs;
    }
    /*EwiseMod*/
    template<typename VType>
    auto arithmEwiseMod(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseMod>(),VType
    >{
        return rhs%lhs;
    }
    /*Add*/
    template<typename VType>
    auto arithmAdd(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Add>(),VType
    >{
        return rhs+lhs;
    }
    /*Sub*/
    template<typename VType>
    auto arithmSub(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Sub>(),VType
    >{
        return rhs-lhs;
    }
    /*MatMul*/
    template<typename Lhs,typename Rhs,typename VType=typename Lhs::value_type>
    auto arithmMatMul(const Lhs &lhs,const Rhs &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::MatMul>(),VType
    >{
        VType rsl{};
        for(std::size_t idx=0;idx<lhs.size();++idx){
            rsl+=lhs(idx)*rhs(idx);
        }
        return rsl;
    }
}//namespace vtx