#include"vtx/Matrix.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType> &Matrix<VType>::operator=(const Matrix &other){
        if(this!=&other){
            rowLength_=other.rowLength_;
            columnLength_=other.columnLength_;
            data_=other.data_;
        }
        return *this;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator+(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix<VType> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]+=other.data_[r];
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator-(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix<VType> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]-=other.data_[r];
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator-() const{
        Matrix<VType> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]=-rsl.data_[r];
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator*(Matrix<VType>::CType s) const{
        Matrix<VType> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]*=s;
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> operator*(typename Matrix<VType>::CType s,const Matrix<VType> &self){
        return self*s;
    }
    template<typename VType>
    std::ostream &operator<<(std::ostream& os,const Matrix<VType>& self){
        for(size_t r=0;r<self.rowLength_;++r){
            if(r==0) os<<"[";
            else os<<" ";
            for(size_t c=0;c<self.columnLength_;++c){
                os<<self.data_[r][c];
                if(c!=self.columnLength_-1) os<<" ";
            }
            if(r==self.rowLength_-1) os<<"]";
            else os<<" ";
            os<<"\n";
        }
        return os;
    }
    template<typename VType>
    Matrix<VType> &Matrix<VType>::operator+=(const Matrix<VType> &other){
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        for(size_t r=0;r<rowLength_;++r){
            data_[r]+=other.data_[r];
        }
        return *this;
    }
    template<typename VType>
    Matrix<VType> &Matrix<VType>::operator-=(const Matrix<VType> &other){
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        for(size_t r=0;r<rowLength_;++r){
            data_[r]-=other.data_[r];
        }
        return *this;
    }
    template<typename VType>
    Matrix<VType> &Matrix<VType>::operator*=(Matrix<VType>::CType s){
        for(size_t r=0;r<rowLength_;++r){
            data_[r]*=s;
        }
        return *this;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator*(const Matrix<VType> &other) const{
        if(columnLength_!=other.rowLength_){
            throw std::invalid_argument("");
        }
        Matrix<VType> rsl(rowLength_,other.columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<other.columnLength_;++c){
                for(size_t i=0;i<columnLength_;++i){
                    rsl[r][c]+=data_[r][i]*other.data_[i][c];
                }
            }
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::operator*(const Vector<VType> &other) const{
        Matrix<VType> matOther=other.toMatrix();
        Matrix<VType> rsl=(*this)*matOther;
        return rsl;
    }
}