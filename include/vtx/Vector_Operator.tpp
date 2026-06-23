#include"vtx/Vector.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename VType>
    Vector<VType> &Vector<VType>::operator=(const Vector<VType> &other){
        if(this!=&other){
            length_=other.length_;
            isColumn_=other.isColumn_;
            data_=other.data_;
        }
        return *this;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::operator+(const Vector<VType> &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector<VType> rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]+=other.data_[i];
        }
        return rsl;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::operator-(const Vector<VType> &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]-=other.data_[i];
        }
        return rsl;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::operator-() const{ 
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]=-rsl.data_[i];
        }
        return rsl;
    }
    template<typename VType>
    Vector<VType> Vector<VType>::operator*(Vector<VType>::CType s) const{
        Vector<VType> rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]*=s;
        }
        return rsl;
    }
    template<typename VType>
    Vector<VType> operator*(typename Vector<VType>::CType s,const Vector<VType> &self){
        return self*s;
    }
    template<typename VType>
    std::ostream &operator<<(std::ostream& os,const Vector<VType>& self){
        if(self.isColumn()){
            for(size_t i=0;i<self.length();i++){
                if(i==0) os<<"[";
                else os<<" ";
                os<<self[i];
                if(i==self.length()-1) os<<"]"<<std::endl;
                else os<<" "<<std::endl;
            }
        }else{
            os<<"[";
            for(size_t i=0;i<self.length();i++){
                if(i==self.length()-1) os<<self[i];
                else os<<self[i]<<" ";
            }
            os<<"]"<<std::endl;
        }
        return os;
    }
    template<typename VType>
    Vector<VType> &Vector<VType>::operator+=(const Vector<VType> &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]+=other.data_[i];
        }
        return *this;
    }
    template<typename VType>
    Vector<VType> &Vector<VType>::operator-=(const Vector<VType> &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]-=other.data_[i];
        }
        return *this;
    }
    template<typename VType>
    Vector<VType> &Vector<VType>::operator*=(Vector<VType>::CType s){
        for(size_t i=0;i<length_;++i){
            data_[i]*=s;
        }
        return *this;
    }
    template<typename VType>
    Matrix<VType> Vector<VType>::operator*(const Vector<VType> &other) const{
        Matrix<VType> matSelf=this->toMatrix();
        Matrix<VType> matOther=other.toMatrix();
        Matrix<VType> rsl=matSelf*matOther;
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Vector<VType>::operator*(const Matrix<VType> &other) const{
        Matrix<VType> matSelf=this->toMatrix();
        Matrix<VType> rsl=matSelf*other;
        return rsl;
    }
}