#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<vector>

#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    /*Sum*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmSum(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprReduction::Sum>(),VType
    >{
        VType rsl{};
        for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
        return rsl;
    }
    /*Max,ArgMax*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMax(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprReduction::Max>(),VType
    >{
        VType rsl=val(0);
        for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i);
        return rsl;
    }
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmArgMax(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprReduction::ArgMax>(),std::size_t
    >{
        auto rsl=val(0);std::size_t tIdx=0;
        for(std::size_t i=0;i<val.size();++i) if(val(i)>rsl) rsl=val(i),tIdx=i;
        return tIdx;
    }
    /*Min,ArgMin*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMin(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprReduction::Min>(),VType
    >{
        VType rsl=val(0);
        for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i);
        return rsl;
    }
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmArgMin(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprReduction::ArgMin>(),std::size_t
    >{
        auto rsl=val(0);std::size_t tIdx=0;
        for(std::size_t i=0;i<val.size();++i) if(val(i)<rsl) rsl=val(i),tIdx=i;
        return tIdx;
    }
    
}//namespace vtx