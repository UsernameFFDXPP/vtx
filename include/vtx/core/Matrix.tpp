#include<algorithm>

#include"Matrix.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType>::Matrix()=default;

    template<typename VType>
    Matrix<VType>::Matrix(std::size_t rowLength,std::size_t colLength,value_type val):
    rowLength_(rowLength),colLength_(colLength),data_(rowLength*colLength,val){}

    template<typename VType>
    Matrix<VType> Matrix<VType>::zeros(size_type rowLength,size_type colLength){
        return Matrix<VType>(rowLength,colLength,VType{});
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::ones(size_type rowLength,size_type colLength){
        return Matrix<VType>(rowLength,colLength,VType{1});
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::identity(size_type length){
        Matrix<VType> rsl=Matrix<VType>::zeros(length,length);
        for(std::size_t i=0;i<length;++i){
            rsl(i,i)=VType{1};
        }
        return rsl;
    }

    template<typename VType>
    std::size_t Matrix<VType>::rowLength() const{
        return rowLength_;
    }
    template<typename VType>
    std::size_t Matrix<VType>::colLength() const{
        return colLength_;
    }
    template<typename VType>
    std::size_t Matrix<VType>::size() const{
        return data_.size();
    }
    template<typename VType>
    bool Matrix<VType>::isEmpty() const{
        return (rowLength_==0 && colLength_==0);
    }

    template<typename VType>
    typename Matrix<VType>::reference Matrix<VType>::operator()(std::size_t row,std::size_t col){
        return data_[row*colLength_+col];
    }
    template<typename VType>
    typename Matrix<VType>::const_reference Matrix<VType>::operator()(std::size_t row,std::size_t col) const{
        return data_[row*colLength_+col];
    }

    template<typename VType>
    Matrix<VType> Matrix<VType>::resized(size_type rowsNew,size_type colsNew) const{
        Matrix<VType> rsl(rowsNew,colsNew);
        std::size_t rows=std::min(rowsNew,rowLength_);
        std::size_t cols=std::min(colsNew,colLength_);
        for(std::size_t row=0;row<rows;++row){
            for(std::size_t col=0;col<cols;++col){
                rsl(row,col)=(*this)(row,col);
            }
        }
        return rsl;
    }
}//namespace vtx