#include"Matrix.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType>::Matrix()=default;

    template<typename VType>
    Matrix<VType>::Matrix(std::size_t rowLength,std::size_t colLength):
        rowLength_(rowLength),colLength_(colLength),data_(rowLength*colLength){}

    template<typename VType>
    std::size_t Matrix<VType>::rowLength() const{
        return rowLength_;
    }

    template<typename VType>
    std::size_t Matrix<VType>::colLength() const{
        return colLength_;
    }

    template<typename VType>
    VType &Matrix<VType>::operator()(std::size_t row,std::size_t col){
        return data_[row*colLength_+col];
    }
    template<typename VType>
    const VType &Matrix<VType>::operator()(std::size_t row,std::size_t col) const{
        return data_[row*colLength_+col];
    }
}