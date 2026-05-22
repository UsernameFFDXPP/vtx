#include"vtx/vector.hpp"
#include"vtx/matrix.hpp"

namespace vtx{
    template<typename T>
    Matrix<T>::Matrix():
        rowLength_(0),columnLength_(0),data_(0,Vector<T>(false)){}
    template<typename T>
    Matrix<T>::Matrix(const std::vector<std::vector<vtype>> &vct):
        rowLength_(vct.size()),columnLength_(vct[0].size()){
            data_.reserve(rowLength_);
            for(size_t r=0;r<rowLength_;++r){
                data_.emplace_back(Vector<T>(vct[r],false));
            }
        }
    template<typename T>
    Matrix<T>::Matrix(size_t r,size_t c,vtype v):
        rowLength_(r),columnLength_(c),data_(r,Vector<T>(c,false,v)){}
    template<typename T>
    Matrix<T>::Matrix(const Matrix<T> &other):
        rowLength_(other.rowLength_),columnLength_(other.columnLength_),data_(other.data_){}
    template<typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<vtype>> init):
        rowLength_(init.size()),columnLength_(init.begin()->size()){
            data_.reserve(rowLength_);
            for(auto &row:init){
                data_.emplace_back(Vector<T>(row,false));
            }
        }
    template<typename T>
    Matrix<T>::~Matrix()=default;

    template<typename T>
    Vector<T> &Matrix<T>::operator[](size_t i){
        return data_[i];
    }
    template<typename T>
    const Vector<T> &Matrix<T>::operator[](size_t i) const{
        return data_[i];
    }
    template<typename T>
    size_t Matrix<T>::rowLength() const{
        return rowLength_;
    }
    template<typename T>
    size_t Matrix<T>::columnLength() const{
        return columnLength_;
    }
    template<typename T>
    const std::vector<Vector<T>> &Matrix<T>::data() const{
        return data_;
    }

    template<typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &other){
        if(this!=&other){
            rowLength_=other.rowLength_;
            columnLength_=other.columnLength_;
            data_=other.data_;
        }
        return *this;
    }
    template<typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix<T> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]+=other.data_[r];
        }
        return rsl;
    }
    template<typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix<T> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]-=other.data_[r];
        }
        return rsl;
    }
    template<typename T>
    Matrix<T> Matrix<T>::operator*(Matrix<T>::ctype s) const{
        Matrix<T> rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]*=s;
        }
        return rsl;
    }
    template<typename T>
    Matrix<T> operator*(typename Matrix<T>::ctype s,const Matrix<T> &self){
        return self*s;
    }
    template<typename T>
    std::ostream &operator<<(std::ostream& os,const Matrix<T>& self){
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
    template<typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const{
        if(columnLength_!=other.rowLength_){
            throw std::invalid_argument("");
        }
        Matrix<T> rsl(rowLength_,other.columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<other.columnLength_;++c){
                for(size_t i=0;i<columnLength_;++i){
                    rsl[r][c]+=data_[r][i]*other.data_[i][c];
                }
            }
        }
        return rsl;
    }
    template<typename T>
    Matrix<T> Matrix<T>::operator*(const Vector<T> &other) const{
        Matrix<T> matOther=other.toMatrix();
        Matrix<T> rsl=(*this)*matOther;
        return rsl;
    }

    template<typename T>
    std::vector<Vector<T>> Matrix<T>::toVector(bool isColumn) const{
        std::vector<Vector<T>> vList;
        if(isColumn){
            vList.reserve(columnLength_);
            for(size_t c=0;c<columnLength_;++c){
                std::vector<vtype> cVector(rowLength_);
                for(size_t r=0;r<rowLength_;++r){
                    cVector[r]=data_[r][c];
                }
                vList.emplace_back(Vector<T>(cVector,isColumn));
            }
        }else{
            vList=data_;
        }
        return vList;
    }
    template<typename T>
    Matrix<T> Matrix<T>::iter(Matrix<T> &other,std::function<Matrix<T>::vtype(vtype,vtype)> func) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){

        }
        Matrix<T> rst(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<columnLength_;++c){
                rst.data_[r][c]=func(data_[r][c],other.data_[r][c]);
            }
        }
        return rst;
    }
    template<typename T>
    Matrix<T> Matrix<T>::iter(Vector<T> &vct,std::function<Matrix<T>::vtype(vtype,vtype)> func) const{
        Matrix<T> rst(rowLength_,columnLength_);
        if(vct.isColumn()){
            if(vct.length()!=rowLength_){

            }
            for(size_t c=0;c<columnLength_;++c){
                for(size_t r=0;r<rowLength_;++r){
                    rst.data_[r][c]=func(data_[r][c],vct[r]);
                }
            }
        }else{
            if(vct.length()!=columnLength_){

            }
            for(size_t r=0;r<rowLength_;++r){
                for(size_t c=0;c<columnLength_;++c){
                    rst.data_[r][c]=func(data_[r][c],vct[c]);
                }
            }
        }
        return rst;
    }
    template<typename T>
    Matrix<T> Matrix<T>::trans(bool isMaindiag) const{
        Matrix<T> transM(columnLength_,rowLength_);
        if(isMaindiag){
            for(size_t r=0;r<rowLength_;++r){
                for(size_t c=0;c<columnLength_;++c){
                    transM.data_[c][r]=data_[r][c];
                }
            }
        }else{
            for(size_t r=0;r<rowLength_;++r){
                for(size_t c=0;c<columnLength_;++c){
                    transM.data_[c][r]=data_[rowLength_-1-r][columnLength_-1-c];
                }
            }
        }
        return transM;
    }
    template<typename T>
    Matrix<T> Matrix<T>::flip(bool isVertical) const{
        Matrix<T> flipM(*this);
        if(isVertical){
            std::reverse(flipM.data_.begin(),flipM.data_.end());
        }else{
            for(auto &row:flipM.data_){
                row=row.flip();
            }
        }
        return flipM;
    }
    template<typename T>
    Matrix<T> Matrix<T>::getDiag() const{
        Matrix<T> diag(rowLength_,columnLength_);
        size_t minDim=rowLength_<columnLength_?rowLength_:columnLength_;
        for(size_t i=0;i<minDim;++i){
            diag.data_[i][i]=data_[i][i];
        }
        return diag;
    }
    template<typename T>
    Matrix<T> Matrix<T>::getUTrig() const{
        Matrix<T> uTrig(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=r;c<columnLength_;++c){
                uTrig.data_[r][c]=data_[r][c];
            }
        }
        return uTrig;
    }
    template<typename T>
    Matrix<T> Matrix<T>::getLTrig() const{
    Matrix<T> lTrig(rowLength_,columnLength_);
    for(size_t c=0;c<columnLength_;++c){
        for(size_t r=c;r<rowLength_;++r){
            lTrig.data_[r][c]=data_[r][c];
        }
    }
    return lTrig;
}
}