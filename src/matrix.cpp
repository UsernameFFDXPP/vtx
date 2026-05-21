#include"vtx/vector.hpp"
#include"vtx/matrix.hpp"

namespace vtx{
    Matrix::Matrix():
        rowLength_(0),columnLength_(0),data_(0,Vector(false)){}
    Matrix::Matrix(const std::vector<std::vector<vtype>> &vct):
        rowLength_(vct.size()),columnLength_(vct[0].size()){
            data_.reserve(rowLength_);
            for(size_t r=0;r<rowLength_;++r){
                data_.emplace_back(Vector(vct[r],false));
            }
        }
    Matrix::Matrix(size_t r,size_t c,vtype v):
        rowLength_(r),columnLength_(c),data_(r,Vector(c,false,v)){}
    Matrix::Matrix(const Matrix &other):
        rowLength_(other.rowLength_),columnLength_(other.columnLength_),data_(other.data_){}
    Matrix::Matrix(std::initializer_list<std::initializer_list<vtype>> init):
        rowLength_(init.size()),columnLength_(init.begin()->size()){
            data_.reserve(rowLength_);
            for(auto &row:init){
                data_.emplace_back(Vector(row,false));
            }
        }
    Matrix::~Matrix()=default;

    Vector &Matrix::operator[](size_t i){
        return data_[i];
    }
    const Vector &Matrix::operator[](size_t i) const{
        return data_[i];
    }
    size_t Matrix::rowLength() const{
        return rowLength_;
    }
    size_t Matrix::columnLength() const{
        return columnLength_;
    }
    const std::vector<Vector> &Matrix::data() const{
        return data_;
    }

    Matrix &Matrix::operator=(const Matrix &other){
        if(this!=&other){
            rowLength_=other.rowLength_;
            columnLength_=other.columnLength_;
            data_=other.data_;
        }
        return *this;
    }
    Matrix Matrix::operator+(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]+=other.data_[r];
        }
        return rsl;
    }
    Matrix Matrix::operator-(const Matrix &other) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){
            throw std::invalid_argument("");
        }
        Matrix rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]-=other.data_[r];
        }
        return rsl;
    }
    Matrix Matrix::operator*(Matrix::ctype s) const{
        Matrix rsl(*this);
        for(size_t r=0;r<rowLength_;++r){
            rsl.data_[r]*=s;
        }
        return rsl;
    }
    Matrix operator*(Matrix::ctype s,const Matrix &self){
        return self*s;
    }
    std::ostream &operator<<(std::ostream& os,const Matrix& self){
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
    Matrix Matrix::operator*(const Matrix &other) const{
        if(columnLength_!=other.rowLength_){
            throw std::invalid_argument("");
        }
        Matrix rsl(rowLength_,other.columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<other.columnLength_;++c){
                for(size_t i=0;i<columnLength_;++i){
                    rsl[r][c]+=data_[r][i]*other.data_[i][c];
                }
            }
        }
        return rsl;
    }
    Matrix Matrix::operator*(const Vector &other) const{
        Matrix matOther=other.toMatrix();
        Matrix rsl=(*this)*matOther;
        return rsl;
    }

    std::vector<Vector> Matrix::toVector(bool isColumn) const{
        std::vector<Vector> vList;
        if(isColumn){
            vList.reserve(columnLength_);
            for(size_t c=0;c<columnLength_;++c){
                std::vector<vtype> cVector(rowLength_);
                for(size_t r=0;r<rowLength_;++r){
                    cVector[r]=data_[r][c];
                }
                vList.emplace_back(Vector(cVector,isColumn));
            }
        }else{
            vList=data_;
        }
        return vList;
    }
    Matrix Matrix::iter(Matrix &other,std::function<Matrix::vtype(vtype,vtype)> func) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){

        }
        Matrix rst(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<columnLength_;++c){
                rst.data_[r][c]=func(data_[r][c],other.data_[r][c]);
            }
        }
        return rst;
    }
    Matrix Matrix::iter(Vector &vct,std::function<Matrix::vtype(vtype,vtype)> func) const{
        Matrix rst(rowLength_,columnLength_);
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
    Matrix Matrix::trans(bool isMaindiag) const{
        Matrix transM(columnLength_,rowLength_);
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
    Matrix Matrix::flip(bool isVertical) const{
        Matrix flipM(*this);
        if(isVertical){
            std::reverse(flipM.data_.begin(),flipM.data_.end());
        }else{
            for(auto &row:flipM.data_){
                row=row.flip();
            }
        }
        return flipM;
    }
    Matrix Matrix::getDiag() const{
        Matrix diag(rowLength_,columnLength_);
        size_t minDim=rowLength_<columnLength_?rowLength_:columnLength_;
        for(size_t i=0;i<minDim;++i){
            diag.data_[i][i]=data_[i][i];
        }
        return diag;
    }
    Matrix Matrix::getUTrig() const{
        Matrix uTrig(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=r;c<columnLength_;++c){
                uTrig.data_[r][c]=data_[r][c];
            }
        }
        return uTrig;
    }
    Matrix Matrix::getLTrig() const{
    Matrix lTrig(rowLength_,columnLength_);
    for(size_t c=0;c<columnLength_;++c){
        for(size_t r=c;r<rowLength_;++r){
            lTrig.data_[r][c]=data_[r][c];
        }
    }
    return lTrig;
}
}