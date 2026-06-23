#include"vtx/Matrix.hpp"
#include"vtx/Range.hpp"

namespace vtx{
    template<typename VType>
    std::vector<Vector<VType>> Matrix<VType>::toVector(bool isColumn) const{
        std::vector<Vector<VType>> vList;
        if(isColumn){
            vList.reserve(columnLength_);
            for(size_t c=0;c<columnLength_;++c){
                std::vector<VType> cVector(rowLength_);
                for(size_t r=0;r<rowLength_;++r){
                    cVector[r]=data_[r][c];
                }
                vList.emplace_back(Vector<VType>(cVector,isColumn));
            }
        }else{
            vList=data_;
        }
        return vList;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::combine(const Matrix<VType> &other,std::function<VType(VType,VType)> func) const{
        if(rowLength_!=other.rowLength_ || columnLength_!=other.columnLength_){

        }
        Matrix<VType> rst(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=0;c<columnLength_;++c){
                rst.data_[r][c]=func(data_[r][c],other.data_[r][c]);
            }
        }
        return rst;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::combine(const Vector<VType> &vct,std::function<VType(VType,VType)> func) const{
        Matrix<VType> rst(rowLength_,columnLength_);
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
    template<typename VType>
    Matrix<VType> Matrix<VType>::trans(bool isMaindiag) const{
        Matrix<VType> transM(columnLength_,rowLength_);
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
    template<typename VType>
    Matrix<VType> Matrix<VType>::flip(bool isVertical) const{
        Matrix<VType> flipM(*this);
        if(isVertical){
            std::reverse(flipM.data_.begin(),flipM.data_.end());
        }else{
            for(auto &row:flipM.data_){
                row=row.flip();
            }
        }
        return flipM;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::swap(size_t idx1,size_t idx2,bool isVertical) const{
        Matrix<VType> swapM(*this);
        if(isVertical){
            std::swap(swapM.data_[idx1],swapM.data_[idx2]);
        }else{
            for(auto &row:swapM.data_){
                std::swap(row[idx1],row[idx2]);
            }
        }
        return swapM;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::slice(const Range &rRange,const Range &cRange) const{
        size_t rLower=rRange.isNoLower()?0:rRange.lower();
        size_t rUpper=rRange.isNoUpper()?rowLength_:rRange.upper();
        size_t cLower=cRange.isNoLower()?0:cRange.lower();
        size_t cUpper=cRange.isNoUpper()?columnLength_:cRange.upper();
        Matrix<VType> rsl(rUpper-rLower,cUpper-cLower);
        for(size_t r=rLower;r<rUpper;++r){
            rsl.data_[r-rLower]=data_[r].slice(cRange);
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::getDiag() const{
        Matrix<VType> diag(rowLength_,columnLength_);
        size_t minDim=rowLength_<columnLength_?rowLength_:columnLength_;
        for(size_t i=0;i<minDim;++i){
            diag.data_[i][i]=data_[i][i];
        }
        return diag;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::getUTrig() const{
        Matrix<VType> uTrig(rowLength_,columnLength_);
        for(size_t r=0;r<rowLength_;++r){
            for(size_t c=r;c<columnLength_;++c){
                uTrig.data_[r][c]=data_[r][c];
            }
        }
        return uTrig;
    }
    template<typename VType>
    Matrix<VType> Matrix<VType>::getLTrig() const{
        Matrix<VType> lTrig(rowLength_,columnLength_);
        for(size_t c=0;c<columnLength_;++c){
            for(size_t r=c;r<rowLength_;++r){
                lTrig.data_[r][c]=data_[r][c];
            }
        }
        return lTrig;
    }
}