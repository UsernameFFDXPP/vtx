#include"vtx/Vector.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename T>
    Vector<T>::Vector():
        length_(0),isColumn_(true),data_(0){}
    template<typename T>
    Vector<T>::Vector(const std::vector<Vector::vtype> &vct,bool isColumn):
        length_(vct.size()),isColumn_(isColumn),data_(vct){}
    template<typename T>
    Vector<T>::Vector(bool isColumn):
        length_(0),isColumn_(isColumn),data_(0){}
    template<typename T>
    Vector<T>::Vector(size_t length,bool isColumn,vtype value):
        length_(length),isColumn_(isColumn),data_(length,value){}
    template<typename T>
    Vector<T>::Vector(const Vector &other):
        length_(other.length_),isColumn_(other.isColumn_),data_(other.data_){}
    template<typename T>
    Vector<T>::Vector(std::initializer_list<vtype> init,bool isColumn):
        length_(init.size()),isColumn_(isColumn),data_(init){}
    template<typename T>
    Vector<T>::~Vector()=default;

    template<typename T>
    typename Vector<T>::vtype &Vector<T>::operator[](size_t i){
        return data_[i];
    }
    template<typename T>
    const typename Vector<T>::vtype &Vector<T>::operator[](size_t i) const{
        return data_[i];
    }
    template<typename T>
    size_t Vector<T>::length() const{
        return length_;
    }
    template<typename T>
    bool Vector<T>::isColumn() const{
        return isColumn_;
    }
    template<typename T>
    const std::vector<typename Vector<T>::vtype> &Vector<T>::data() const{
        return data_;
    }

    template<typename T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &other){
        if(this!=&other){
            length_=other.length_;
            isColumn_=other.isColumn_;
            data_=other.data_;
        }
        return *this;
    }
    template<typename T>
    Vector<T> Vector<T>::operator+(const Vector<T> &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector<T> rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]+=other.data_[i];
        }
        return rsl;
    }
    template<typename T>
    Vector<T> Vector<T>::operator-(const Vector<T> &other) const{ 
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        Vector rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]-=other.data_[i];
        }
        return rsl;
    }
    template<typename T>
    Vector<T> Vector<T>::operator*(Vector<T>::ctype s) const{
        Vector<T> rsl((*this));
        for(size_t i=0;i<length_;++i){
            rsl.data_[i]*=s;
        }
        return rsl;
    }
    template<typename T>
    Vector<T> operator*(typename Vector<T>::ctype s,const Vector<T> &self){
        return self*s;
    }
    template<typename T>
    std::ostream &operator<<(std::ostream& os,const Vector<T>& self){
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
    template<typename T>
    Vector<T> &Vector<T>::operator+=(const Vector<T> &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]+=other.data_[i];
        }
        return *this;
    }
    template<typename T>
    Vector<T> &Vector<T>::operator-=(const Vector<T> &other){
        if(length_!=other.length_ || isColumn_!=other.isColumn_){
            throw std::invalid_argument("");
        }
        for(size_t i=0;i<length_;++i){
            data_[i]-=other.data_[i];
        }
        return *this;
    }
    template<typename T>
    Vector<T> &Vector<T>::operator*=(ctype s){
        for(size_t i=0;i<length_;++i){
            data_[i]*=s;
        }
        return *this;
    }
    template<typename T>
    Matrix<T> Vector<T>::operator*(const Vector<T> &other) const{
        Matrix<T> matSelf=this->toMatrix();
        Matrix<T> matOther=other.toMatrix();
        Matrix<T> rsl=matSelf*matOther;
        return rsl;
    }
    template<typename T>
    Matrix<T> Vector<T>::operator*(const Matrix<T> &other) const{
        Matrix<T> matSelf=this->toMatrix();
        Matrix<T> rsl=matSelf*other;
        return rsl;
    }

    template<typename T>
    typename Vector<T>::iterator Vector<T>::begin(){return data_.begin();}
    template<typename T>
    typename Vector<T>::iterator Vector<T>::end(){return data_.end();}
    template<typename T>
    typename Vector<T>::const_iterator Vector<T>::begin() const{return data_.begin();}
    template<typename T>
    typename Vector<T>::const_iterator Vector<T>::end() const{return data_.end();}

    template<typename T>
    Matrix<T> Vector<T>::toMatrix() const{
        Matrix<T> rsl;
        if(isColumn_){
            rsl=Matrix<T>(length_,1);
            for(size_t i=0;i<length_;++i){
                rsl[i][0]=data_[i];
            }
        }else{
            rsl=Matrix<T>(1,length_);
            for(size_t i=0;i<length_;++i){
                rsl[0][i]=data_[i];
            }
        }
        return rsl;
    }
    template<typename T>
    Vector<T> Vector<T>::combine(Vector &other,std::function<vtype(vtype,vtype)> func) const{
        if(length_!=other.length_ || isColumn_!=other.isColumn_){

        }
        Vector<T> rst(length_,isColumn_);
        for(size_t i=0;i<length_;++i){
            rst.data_[i]=func(data_[i],other.data_[i]);
        }
        return rst;
    }
    template<typename T>
    Vector<T> Vector<T>::trans() const{
        Vector<T> transV(data_,!isColumn_);
        return transV;
    }
    template<typename T>
    Vector<T> Vector<T>::flip() const{
        Vector<T> flipV(*this);
        std::reverse(flipV.data_.begin(),flipV.data_.end());
        return flipV;
    }
    template<typename T>
    Vector<T> Vector<T>::slice(const Range &range) const{
        size_t rLower=range.isNoLower()?0:range.lower();
        size_t rUpper=range.isNoUpper()?length_:range.upper();
        return Vector<T>(std::vector<T>(data_.begin()+rLower,data_.begin()+rUpper),isColumn_);
    }
    template<typename T>
    typename Vector<T>::vtype Vector<T>::norm(const double &p) const{
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