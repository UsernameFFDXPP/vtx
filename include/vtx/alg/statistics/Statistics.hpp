#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<vector>
#include<cstdlib>

#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    /*Covariance*/
    /*Correlation*/
    /*Mean*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmMean(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprStatistics::Mean>(),VType
    >{
        VType rsl{};
        for(std::size_t i=0;i<val.size();++i) rsl+=val(i);
        return rsl/static_cast<VType>(val.size());
    }
    /*Variance*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmVariance(const Line &val)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprStatistics::Variance>(),VType
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
        opr_traits::getOprDemand<VType,OprStatistics::SampleVariance>(),VType
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
        opr_traits::getOprDemand<VType,OprStatistics::Median>(),VType
    >{
        std::vector<VType> temp(val.size());
        for(std::size_t i=0;i<val.size();++i) temp[i]=val(i);
        std::size_t idx=temp.size()/2;
        std::nth_element(temp.begin(),temp.begin()+idx,temp.end());
        if(temp.size()%2==1) return temp[idx];
        auto it=std::max_element(temp.begin(),temp.begin()+idx);
        return (*it+temp[idx])/static_cast<VType>(2);
    }
    /*Center*/
        //Mean+Sub
    /*Standardize*/
        //Variance+EwiseDiv
    /*Quantile*/
    template<typename Line,typename VType=typename Line::value_type>
    auto arithmQuantile(const Line &val,double q)->std::enable_if_t<
        opr_traits::getOprDemand<VType,OprStatistics::Quantile>(),VType
    >{
        std::vector<VType> temp(val.size());
        for(std::size_t i=0;i<val.size();++i) temp[i]=val(i);
        double pos=(temp.size()-1)*q;
        std::size_t idx=static_cast<std::size_t>(pos);
        double fraction=pos-idx;
        std::nth_element(temp.begin(),temp.begin()+idx,temp.end());
        if(fraction==0) return temp[idx];
        VType next=*std::min_element(temp.begin()+idx+1,temp.end());
        return temp[idx]*static_cast<VType>(1-fraction)+next*static_cast<VType>(fraction);
    }
}//namespace vtx