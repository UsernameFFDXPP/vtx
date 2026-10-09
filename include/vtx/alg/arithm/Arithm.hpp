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
    auto algNeg(const VType &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Neg>(),VType
    >{
        return -val;
    }
    /*EwiseInv*/
    template<typename VType>
    auto algEwiseInv(const VType &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseInv>(),VType
    >{
        return VType{}/val;
    }
    /*EwiseMul*/
    template<typename VType>
    auto algEwiseMul(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseMul>(),VType
    >{
        return lhs*rhs;
    }
    /*EwiseDiv*/
    template<typename VType>
    auto algEwiseDiv(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>(),VType
    >{
        return lhs/rhs;
    }
    /*EwiseMod*/
    template<typename VType>
    auto algEwiseMod(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::EwiseMod>(),VType
    >{
        return lhs%rhs;
    }
    /*Add*/
    template<typename VType>
    auto algAdd(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Add>(),VType
    >{
        return lhs+rhs;
    }
    /*Sub*/
    template<typename VType>
    auto algSub(const VType &rhs,const VType &lhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::Sub>(),VType
    >{
        return rhs-lhs;
    }
    /*MatMul*/
    template<typename Lhs,typename Rhs,typename VType=typename Lhs::value_type>
    auto algMatMul(const Lhs &lhs,const Rhs &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprArithm::MatMul>(),VType
    >{
        VType rsl{};
        for(std::size_t idx=0;idx<lhs.size();++idx){
            rsl+=lhs(idx)*rhs(idx);
        }
        return rsl;
    }
}//namespace vtx