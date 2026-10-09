#pragma once

#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    /*Equal*/
    template<typename VType>
    auto algEqual(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::Equal>(),bool
    >{
        return lhs==rhs;
    }
    /*Greater*/
    template<typename VType>
    auto algGreater(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::Greater>(),bool
    >{
        return lhs>rhs;
    }
    /*GraeterEqual*/
    template<typename VType>
    auto algGreaterEqual(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::GreaterEqual>(),bool
    >{
        return lhs>=rhs;
    }
    /*Less*/
    template<typename VType>
    auto algLess(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::Less>(),bool
    >{
        return lhs<rhs;
    }
    /*LessEqual*/
    template<typename VType>
    auto algLessEqual(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::LessEqual>(),bool
    >{
        return lhs<=rhs;
    }
    /*NotEqual*/
    template<typename VType>
    auto algNotEqual(const VType &lhs,const VType &rhs)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprCompare::NotEqual>(),bool
    >{
        return lhs!=rhs;
    }
}