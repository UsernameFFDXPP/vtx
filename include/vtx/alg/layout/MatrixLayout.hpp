#pragma once

#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    /*Transpose*/
    template<typename VType>
    Matrix<VType> transpose(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.colLength(),mat.rowLength());
        for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
            rsl(col,row)=mat(row,col);
        }
        return rsl;
    }
    /*Flip*/
    template<typename VType>
    Matrix<VType> flip(const Matrix<VType> &mat,Axis axis){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        if(axis==Axis::Row){
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row,col)=mat(mat.rowLength()-1-row,col);
            }
        }else if(axis==Axis::Col){
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row,col)=mat(row,mat.colLength()-1-col);
            }
        }else if(axis==Axis::None){
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row,col)=mat(mat.rowLength()-1-row,mat.colLength()-1-col);
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
    /*Reshape*/
    template<typename VType>
    Matrix<VType> reshape(const Matrix<VType> &mat,std::size_t rows,std::size_t cols){
        Matrix<VType> rsl(rows,cols);
        for(std::size_t idx=0;idx<mat.size();++idx){
            rsl(idx)=mat(idx);
        }
        return rsl;
    }
    /*Resize*/
    template<typename VType>
    Matrix<VType> resize(const Matrix<VType> &mat,std::size_t rowsNew,std::size_t colsNew){
        Matrix<VType> rsl(rowsNew,colsNew);
        std::size_t rows=std::min(rowsNew,mat.rowLength());
        std::size_t cols=std::min(colsNew,mat.colLength());
        for(std::size_t row=0;row<rows;++row){
            for(std::size_t col=0;col<cols;++col){
                rsl(row,col)=mat(row,col);
            }
        }
        return rsl;
    }
    /*Insert*/
    template<typename VType>
    Matrix<VType> insert(const Matrix<VType> &mat,Axis axis,std::size_t idx){
        Matrix<VType> rsl;
        if(axis==Axis::Row){
            rsl=Matrix<VType>(mat.rowLength()+1,mat.colLength());
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(row<idx) rsl(row,col)=mat(row,col);
                else rsl(row+1,col)=mat(row,col);
            }
        }else if(axis==Axis::Col){
            rsl=Matrix<VType>(mat.rowLength(),mat.colLength()+1);
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(col<idx) rsl(row,col)=mat(row,col);
                else rsl(row,col+1)=mat(row,col);
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
    /*Drop*/
    template<typename VType>
    Matrix<VType> drop(const Matrix<VType> &mat,Axis axis,std::size_t idx){
        Matrix<VType> rsl;
        if(axis==Axis::Row){
            rsl=Matrix<VType>(mat.rowLength()-1,mat.colLength());
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(row<idx) rsl(row,col)=mat(row,col);
                if(row>idx) rsl(row-1,col)=mat(row,col);
            }
        }else if(axis==Axis::Col){
            rsl=Matrix<VType>(mat.rowLength(),mat.colLength()-1);
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(col<idx) rsl(row,col)=mat(row,col);
                if(col>idx) rsl(row,col-1)=mat(row,col);
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
    /*Swap*/
    template<typename VType>
    Matrix<VType> swap(const Matrix<VType> &mat,Axis axis,std::size_t idx1,std::size_t idx2){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        if(axis==Axis::Row){
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(row==idx1) rsl(row,col)=mat(idx2,col);
                if(row==idx2) rsl(row,col)=mat(idx1,col);
            }
        }else if(axis==Axis::Col){
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=0;col<mat.colLength();++col){
                if(col==idx1) rsl(row,col)=mat(row,idx2);
                if(col==idx2) rsl(row,col)=mat(row,idx1);
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
    /*Slice*/
    template<typename VType>
    Matrix<VType> slice(const Matrix<VType> &mat,Axis axis,std::size_t idx1,std::size_t idx2){
        Matrix<VType> rsl;
        if(axis==Axis::Row){
            rsl=Matrix<VType>(idx2-idx1,mat.colLength());
            for(std::size_t row=idx1;row<idx2;++row) for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row-idx1,col)=mat(row,col);
            }
        }else if(axis==Axis::Col){
            rsl=Matrix<VType>(mat.rowLength(),idx2-idx1);
            for(std::size_t row=0;row<mat.rowLength();++row) for(std::size_t col=idx1;col<idx2;++col){
                rsl(row,col-idx1)=mat(row,col);
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
    /*Concat*/
    template<typename VType>
    Matrix<VType> concat(const Matrix<VType> &mat1,const Matrix<VType> &mat2,Axis axis){
        Matrix<VType> rsl;
        if(axis==Axis::Row){
            std::size_t rows=mat1.rowLength()+mat2.rowLength();
            std::size_t cols=mat1.colLength();
            rsl=Matrix<VType>(rows,cols);
            for(std::size_t row=0;row<rows;++row) for(std::size_t col=0;col<cols;++col){
                if(row<mat1.rowLength()) rsl(row,col)=mat1(row,col);
                else rsl(row,col)=mat2(row-mat1.rowLength(),col);
            }
        }else if(axis==Axis::Col){
            std::size_t rows=mat1.rowLength();
            std::size_t cols=mat1.colLength()+mat2.colLength();
            rsl=Matrix<VType>(rows,cols);
            for(std::size_t row=0;row<rows;++row) for(std::size_t col=0;col<cols;++col){
                if(col<mat1.colLength()) rsl(row,col)=mat1(row,col);
                else rsl(row,col)=mat2(row,col-mat1.colLength());
            }
        }else{
            /*Axis Error*/
        }
        return rsl;
    }
}