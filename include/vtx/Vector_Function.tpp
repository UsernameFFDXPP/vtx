#include"vtx/Vector.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType> Vector<VType>::toMatrix() const{
        Matrix<VType> rsl;
        if(isColumn_){
            rsl=Matrix<VType>(length_,1);
            for(size_t i=0;i<length_;++i){
                rsl[i][0]=data_[i];
            }
        }else{
            rsl=Matrix<VType>(1,length_);
            for(size_t i=0;i<length_;++i){
                rsl[0][i]=data_[i];
            }
        }
        return rsl;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::combine(const Vector<VType> &other,std::function<VType(VType,VType)> func) const{
        if(length_!=other.length_ || isColumn_!=other.isColumn_){

        }
        Vector<VType> rst(length_,isColumn_);
        for(size_t i=0;i<length_;++i){
            rst.data_[i]=func(data_[i],other.data_[i]);
        }
        return rst;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::trans() const{
        Vector<VType> transV(data_,!isColumn_);
        return transV;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::flip() const{
        Vector<VType> flipV(*this);
        std::reverse(flipV.data_.begin(),flipV.data_.end());
        return flipV;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::swap(size_t idx1,size_t idx2) const{
        Vector<VType> swapV(*this);
        std::swap(swapV.data_[idx1],swapV.data_[idx2]);
        return swapV;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::slice(const Range &range) const{
        size_t rLower=range.isNoLower()?0:range.lower();
        size_t rUpper=range.isNoUpper()?length_:range.upper();
        return Vector<VType>(std::vector<VType>(data_.begin()+rLower,data_.begin()+rUpper),isColumn_);
    }
    template<typename VType>
    VType Vector<VType>::norm(double p){
        if(p==0){
            size_t count=0;
            for(double value:data_){
                if(value!=0.0) ++count;
            }
            return static_cast<double>(count);
        }else if(p==std::numeric_limits<double>::infinity()){
            double max=0.0;
            for(double value:data_){
                double temp=std::abs(value);
                if(temp>max) max=temp;
            }
            return max;
        }else{
            double rsl=0.0;
            for(double value:data_){
                rsl+=std::pow(std::abs(value),p);
            }
            return std::pow(rsl,1.0/p);
        }
    }
}