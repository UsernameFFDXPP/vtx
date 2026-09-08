#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    namespace arithmmap{
        template<typename VType>
        void unaryEwiseMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &mat){
            for(std::size_t row=0;row<mat.rowLength();++row){
                for(std::size_t col=0;col<mat.colLength();++col){
                    rsl(row,col)=unaryEwiseArithm(opr,mat(row,col));
                }
            }
        }

        template<typename VType>
        void binaryEwiseMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<lhs.rowLength();++row){
                for(std::size_t col=0;col<lhs.colLength();++col){
                    rsl(row,col)=binaryEwiseArithm(opr,lhs(row,col),rhs(row,col));
                }
            }
        }

        template<typename VType>
        void broadcastEwiseMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<lhs.rowLength();++row){
                for(std::size_t col=0;col<lhs.colLength();++col){
                    rsl(row,col)=binaryEwiseArithm(opr,lhs(row,col),rhs(row%rhs.rowLength(),col%rhs.colLength()));
                }
            }
        }
        template<typename VType>
        void broadcastEwiseMap(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const VType &arg){
            for(std::size_t row=0;row<lhs.rowLength();++row){
                for(std::size_t col=0;col<lhs.colLength();++col){
                    rsl(row,col)=binaryEwiseArithm(opr,lhs(row,col),arg);
                }
            }
        }
        template<typename VType>
        void broadcastEwiseMap(Matrix<VType> &rsl,Operation opr,const VType &arg,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rhs.rowLength();++row){
                for(std::size_t col=0;col<rhs.colLength();++col){
                    rsl(row,col)=binaryEwiseArithm(opr,arg,rhs(row,col));
                }
            }
        }
    }

    /*Neg*/
    template<typename VType>
    Matrix<VType> neg(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::unaryEwiseMap(rsl,Operation::Neg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &neg_(Matrix<VType> &mat){
        arithmmap::unaryEwiseMap(mat,Operation::Neg,mat);
        return mat;
    }
    /*EwiseInv*/
    template<typename VType>
    Matrix<VType> ewiseInv(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::unaryEwiseMap(rsl,Operation::EwiseInv,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseInv_(Matrix<VType> &mat){
        arithmmap::unaryEwiseMap(mat,Operation::EwiseInv,mat);
        return mat;
    }
    /*EwiseMul*/
    template<typename VType>
    Matrix<VType> ewiseMul(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseMul,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMul_(Matrix<VType> &mat,const VType &arg){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseMul,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseMul(VType arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseMul,mat,arg);
        return rsl;
    }
        template<typename VType>
    Matrix<VType> &ewiseMul_(VType arg,Matrix<VType> &mat){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseMul,mat,arg);
        return mat;
    }
    /*EwiseDiv*/
    template<typename VType>
    Matrix<VType> ewiseDiv(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseDiv,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseDiv_(Matrix<VType> &mat,const VType &arg){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseDiv,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseDiv(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseDiv,arg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseDiv_(const VType &arg,Matrix<VType> &mat){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseDiv,arg,mat);
        return mat;
    }
    /*EwiseMod*/
    template<typename VType>
    Matrix<VType> ewiseMod(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseMod,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMod_(Matrix<VType> &mat,const VType &arg){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseMod,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseMod(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithmmap::broadcastEwiseMap(rsl,Operation::EwiseMod,arg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMod_(const VType &arg,Matrix<VType> &mat){
        arithmmap::broadcastEwiseMap(mat,Operation::EwiseMod,arg,mat);
        return mat;
    }
    /*Add*/
    template<typename VType>
    Matrix<VType> add(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        arithmmap::binaryEwiseMap(rsl,Operation::Add,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &add_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        arithmmap::binaryEwiseMap(lhs,Operation::Add,lhs,rhs);
        return lhs;
    }
    /*Sub*/
    template<typename VType>
    Matrix<VType> sub(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        arithmmap::binaryEwiseMap(rsl,Operation::Sub,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &sub_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        arithmmap::binaryEwiseMap(lhs,Operation::Sub,lhs,rhs);
        return lhs;
    }
    /*MatInv*/
    template<typename VType>
    Matrix<VType> matInv(const Matrix<VType> &mat);
    /*Transpose*/
    template<typename VType>
    Matrix<VType> transpose(const Matrix<VType> &mat);
    /*MatMul*/
    template<typename VType>
    Matrix<VType> matMul(const Matrix<VType> &lhs,const Matrix<VType> &rhs);
}