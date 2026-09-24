#include"Storage.hpp"

namespace vtx{
    template<typename VType>
    Storage<VType>::Storage(std::size_t size,VType val):
    data_(size,val){}

    template<typename VType>
    std::size_t Storage<VType>::size() const{
        return data_.size();
    }

    template<typename VType>
    VType &Storage<VType>::operator[](std::size_t index){
        return data_[index];
    }
    template<typename VType>
    const VType &Storage<VType>::operator[](std::size_t index) const{
        return data_[index];
    }
    /*
    template<typename VType>
    typename Storage<VType>::iterator Storage<VType>::begin(){
        return data_.begin();
    }
    template<typename VType>
    typename Storage<VType>::const_iterator Storage<VType>::begin() const{
        return data_.cbegin();
    }

    template<typename VType>
    typename Storage<VType>::iterator Storage<VType>::end(){
        return data_.end();
    }
    template<typename VType>
    typename Storage<VType>::const_iterator Storage<VType>::end() const{
        return data_.cend();
    }
    */
    template<typename VType>
    void Storage<VType>::resize(std::size_t size){
        data_.resize(size);
    }
}//namespace vtx