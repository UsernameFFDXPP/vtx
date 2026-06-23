#include"vtx/Vector.hpp"
#include"vtx/Range.hpp"

namespace vtx{
        template<typename VType>
    Vector<VType>::Vector():
        length_(0),isColumn_(true),data_(0){}
    template<typename VType>
    Vector<VType>::Vector(const std::vector<VType> &vct,bool isColumn):
        length_(vct.size()),isColumn_(isColumn),data_(vct){}
    template<typename VType>
    Vector<VType>::Vector(bool isColumn):
        length_(0),isColumn_(isColumn),data_(0){}
    template<typename VType>
    Vector<VType>::Vector(size_t length,bool isColumn,VType value):
        length_(length),isColumn_(isColumn),data_(length,value){}
    template<typename VType>
    Vector<VType>::Vector(const Vector &other):
        length_(other.length_),isColumn_(other.isColumn_),data_(other.data_){}
    template<typename VType>
    Vector<VType>::Vector(std::initializer_list<VType> init,bool isColumn):
        length_(init.size()),isColumn_(isColumn),data_(init){}
    template<typename VType>
    Vector<VType>::~Vector()=default;

    template<typename VType>
    VType &Vector<VType>::operator[](size_t i){
        return data_[i];
    }
    template<typename VType>
    const VType &Vector<VType>::operator[](size_t i) const{
        return data_[i];
    }
    template<typename VType>
    size_t Vector<VType>::length() const{
        return length_;
    }
    template<typename VType>
    bool Vector<VType>::isColumn() const{
        return isColumn_;
    }
    template<typename VType>
    const std::vector<VType> &Vector<VType>::data() const{
        return data_;
    }

    template<typename VType>
    typename Vector<VType>::iterator Vector<VType>::begin(){return data_.begin();}
    template<typename VType>
    typename Vector<VType>::iterator Vector<VType>::end(){return data_.end();}
    template<typename VType>
    typename Vector<VType>::const_iterator Vector<VType>::begin() const{return data_.begin();}
    template<typename VType>
    typename Vector<VType>::const_iterator Vector<VType>::end() const{return data_.end();}
}