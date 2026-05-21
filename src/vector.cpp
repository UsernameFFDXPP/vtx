#include"vtx/vector.hpp"
#include"vtx/matrix.hpp"

namespace vtx{
    Vector::Vector(bool isColumn):
        length_(0),isColumn_(isColumn),data_(0){}
    Vector::Vector(const std::vector<Vector::vtype> &vct,bool isColumn):
        length_(vct.size()),isColumn_(isColumn),data_(vct){}
    Vector::Vector(size_t length,bool isColumn,vtype value):
        length_(length),isColumn_(isColumn),data_(length,value){}
    Vector::Vector(const Vector &other):
        length_(other.length_),isColumn_(other.isColumn_),data_(other.data_){}
    Vector::Vector(std::initializer_list<vtype> init,bool isColumn):
        length_(init.size()),isColumn_(isColumn),data_(init){}
    Vector::~Vector()=default;

    Vector::vtype &Vector::operator[](size_t i){
        return data_[i];
    }
    const Vector::vtype &Vector::operator[](size_t i) const{
        return data_[i];
    }
    size_t Vector::length() const{
        return length_;
    }
    bool Vector::isColumn() const{
        return isColumn_;
    }
    const std::vector<Vector::vtype> &Vector::data() const{
        return data_;
    }

    Vector &Vector::operator=(const Vector &other){
        if(this!=&other){
            length_=other.length_;
            isColumn_=other.isColumn_;
            data_=other.data_;
        }
        return *this;
    }
    Vector Vector::operator+(const Vector &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]+=other.data_[i];
        }
        return rsl;
    }
    Vector Vector::operator-(const Vector &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]-=other.data_[i];
        }
        return rsl;
    }
    Vector Vector::operator*(Vector::ctype s) const{
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]*=s;
        }
        return rsl;
    }
    Vector operator*(Vector::ctype s,const Vector &self){
        return self*s;
    }
    std::ostream &operator<<(std::ostream& os,const Vector& self){
        if(self.isColumn()){
            for(size_t i=0;i<self.length();i++){
                if(i==0) os<<"["<<self[i]<<" "<<std::endl;
                else if(i==self.length()-1) os<<" "<<self[i]<<"]"<<std::endl;
                else os<<" "<<self[i]<<" "<<std::endl;
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
    Vector &Vector::operator+=(const Vector &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]+=other.data_[i];
        }
        return *this;
    }
    Vector &Vector::operator-=(const Vector &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]-=other.data_[i];
        }
        return *this;
    }
    Vector &Vector::operator*=(ctype s){
        for(size_t i=0;i<length_;++i){
            data_[i]*=s;
        }
        return *this;
    }
    Matrix Vector::operator*(const Vector &other) const{
        Matrix matSelf=this->toMatrix();
        Matrix matOther=other.toMatrix();
        Matrix rsl=matSelf*matOther;
        return rsl;
    }
    Matrix Vector::operator*(const Matrix &other) const{
        Matrix matSelf=this->toMatrix();
        Matrix rsl=matSelf*other;
        return rsl;
    }

    Matrix Vector::toMatrix() const{
        Matrix rsl;
        if(isColumn_){
            rsl=Matrix(length_,1);
            for(size_t i=0;i<length_;++i){
                rsl[i][0]=data_[i];
            }
        }else{
            rsl=Matrix(1,length_);
            for(size_t i=0;i<length_;++i){
                rsl[0][i]=data_[i];
            }
        }
        return rsl;
    }
    Vector Vector::iter(Vector &other,std::function<vtype(vtype,vtype)> func) const{
        if(length_!=other.length_ || isColumn_!=other.isColumn_){

        }
        Vector rst(length_,isColumn_);
        for(size_t i=0;i<length_;++i){
            rst.data_[i]=func(data_[i],other.data_[i]);
        }
        return rst;
    }
    Vector Vector::trans() const{
        Vector transV(data_,!isColumn_);
        return transV;
    }
    Vector Vector::flip() const{
        Vector flipV(*this);
        std::reverse(flipV.data_.begin(),flipV.data_.end());
        return flipV;
    }
    Vector::vtype Vector::norm(const double &p) const{
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