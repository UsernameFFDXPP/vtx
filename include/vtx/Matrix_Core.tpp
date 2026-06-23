#include"vtx/Matrix.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType>::Matrix():
        rowLength_(0),columnLength_(0),data_(0,Vector<VType>(false)){}
    template<typename VType>
    Matrix<VType>::Matrix(const std::vector<std::vector<VType>> &vct):
        rowLength_(vct.size()),columnLength_(vct[0].size()){
            data_.reserve(rowLength_);
            for(size_t r=0;r<rowLength_;++r){
                data_.emplace_back(Vector<VType>(vct[r],false));
            }
        }
    template<typename VType>
    Matrix<VType>::Matrix(size_t r,size_t c,VType value):
        rowLength_(r),columnLength_(c),data_(r,Vector<VType>(c,false,value)){}
    template<typename VType>
    Matrix<VType>::Matrix(const Matrix<VType> &other):
        rowLength_(other.rowLength_),columnLength_(other.columnLength_),data_(other.data_){}
    template<typename VType>
    Matrix<VType>::Matrix(std::initializer_list<std::initializer_list<VType>> init):
        rowLength_(init.size()),columnLength_(init.begin()->size()){
            data_.reserve(rowLength_);
            for(auto &row:init){
                data_.emplace_back(Vector<VType>(row,false));
            }
        }
    template<typename VType>
    Matrix<VType>::~Matrix()=default;

    template<typename VType>
    Vector<VType> &Matrix<VType>::operator[](size_t i){
        return data_[i];
    }
    template<typename VType>
    const Vector<VType> &Matrix<VType>::operator[](size_t i) const{
        return data_[i];
    }
    template<typename VType>
    size_t Matrix<VType>::rowLength() const{
        return rowLength_;
    }
    template<typename VType>
    size_t Matrix<VType>::columnLength() const{
        return columnLength_;
    }
    template<typename VType>
    const std::vector<Vector<VType>> &Matrix<VType>::data() const{
        return data_;
    }
    
    template<typename VType>
    typename Matrix<VType>::iterator Matrix<VType>::begin(){return data_.begin();}
    template<typename VType>
    typename Matrix<VType>::iterator Matrix<VType>::end(){return data_.end();}
    template<typename VType>
    typename Matrix<VType>::const_iterator Matrix<VType>::begin() const{return data_.begin();}
    template<typename VType>
    typename Matrix<VType>::const_iterator Matrix<VType>::end() const{return data_.end();}
}
