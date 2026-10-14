#pragma once

#include<functional>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/View.hpp"
#include"vtx/alg/Map.hpp"
#include"vtx/alg/arithm/Arithm.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    Matrix<VType> neg(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapUnaryEwise(rsl,OprArithm::Neg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &neg_(Matrix<VType> &mat){
        map::mapUnaryEwise(mat,OprArithm::Neg,mat);
        return mat;
    }
    /*EwiseInv*/
    template<typename VType>
    Matrix<VType> ewiseInv(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapUnaryEwise(rsl,OprArithm::EwiseInv,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseInv_(Matrix<VType> &mat){
        map::mapUnaryEwise(mat,OprArithm::EwiseInv,mat);
        return mat;
    }
    /*ScalarMul*/
    template<typename VType>
    Matrix<VType> scalarMul(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarMul,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &scalarMul_(Matrix<VType> &mat,const VType &arg){
        map::mapBroadcastEwise(mat,OprArithm::ScalarMul,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> scalarMul(VType arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarMul,mat,arg);
        return rsl;
    }
    /*ScalarDiv*/
    template<typename VType>
    Matrix<VType> scalarDiv(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarDiv,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &scalarDiv_(Matrix<VType> &mat,const VType &arg){
        map::mapBroadcastEwise(mat,OprArithm::ScalarDiv,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> scalarDiv(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarDiv,arg,mat);
        return rsl;
    }
    /*ScalarMod*/
    template<typename VType>
    Matrix<VType> scalarMod(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarMod,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &scalarMod_(Matrix<VType> &mat,const VType &arg){
        map::mapBroadcastEwise(mat,OprArithm::ScalarMod,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> scalarMod(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        map::mapBroadcastEwise(rsl,OprArithm::ScalarMod,arg,mat);
        return rsl;
    }
    /*Add*/
    template<typename VType>
    Matrix<VType> add(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprArithm::Add,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &add_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        map::mapBinaryEwise(lhs,OprArithm::Add,lhs,rhs);
        return lhs;
    }
    /*Sub*/
    template<typename VType>
    Matrix<VType> sub(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprArithm::Sub,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &sub_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        map::mapBinaryEwise(lhs,OprArithm::Sub,lhs,rhs);
        return lhs;
    }
    /*EwiseMul*/
    template<typename VType>
    Matrix<VType> ewiseMul(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprArithm::EwiseMul,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMul_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        map::mapBinaryEwise(lhs,OprArithm::EwiseMul,lhs,rhs);
        return lhs;
    }
    /*EwiseDiv*/
    template<typename VType>
    Matrix<VType> ewiseDiv(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprArithm::EwiseDiv,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseDiv_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        map::mapBinaryEwise(lhs,OprArithm::EwiseDiv,lhs,rhs);
        return lhs;
    }
    /*EwiseMod*/
    template<typename VType>
    Matrix<VType> ewiseMod(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        map::mapBinaryEwise(rsl,OprArithm::EwiseMod,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMod_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        map::mapBinaryEwise(lhs,OprArithm::EwiseMod,lhs,rhs);
        return lhs;
    }
    /*MatInv*/
    template<typename VType>
    Matrix<VType> matInv(const Matrix<VType> &mat);
    /*MatMul*/
    template<typename VType>
    Matrix<VType> matMul(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),rhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<rhs.colLength();++col){
                rsl(row,col)=algMatMul(View<Matrix<VType>>(&lhs,Axis::Row,row),View<Matrix<VType>>(&rhs,Axis::Col,col));
            }
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &matMul_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),rhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<rhs.colLength();++col){
                rsl(row,col)=algMatMul(View<Matrix<VType>>(&lhs,Axis::Row,row),View<Matrix<VType>>(&rhs,Axis::Col,col));
            }
        }
        lhs=std::move(rsl);
        return lhs;
    }
    /*MatDiv*/
    /*EwiseUnaryFunc*/
    template<typename VTypeI,typename VTypeO>
    Matrix<VTypeO> ewiseUnaryFunc(VTypeO (*func)(VTypeI),const Matrix<VTypeI> &mat){
        Matrix<VTypeO> rsl(mat.rowLength(),mat.colLength());
        for(std::size_t row=0;row<mat.rowLength();++row){
            for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row,col)=func(mat(row,col));
            }
        }
        return rsl;
    }
    template<typename VTypeI,typename VTypeO>
    Matrix<VTypeO> ewiseUnaryFunc(std::function<VTypeO(VTypeI)> func,const Matrix<VTypeI> &mat){
        Matrix<VTypeO> rsl(mat.rowLength(),mat.colLength());
        for(std::size_t row=0;row<mat.rowLength();++row){
            for(std::size_t col=0;col<mat.colLength();++col){
                rsl(row,col)=func(mat(row,col));
            }
        }
        return rsl;
    }
    /*EwiseBinaryFunc*/
    template<typename VTypeI,typename VTypeO>
    Matrix<VTypeO> ewiseBinaryFunc(VTypeO (*func)(VTypeI,VTypeI),const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
        Matrix<VTypeO> rsl(lhs.rowLength(),lhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<rhs.colLength();++col){
                rsl(row,col)=func(lhs(row,col),rhs(row,col));
            }
        }
        return rsl;
    }
    template<typename VTypeI,typename VTypeO>
    Matrix<VTypeO> ewiseBinaryFunc(std::function<VTypeO(VTypeI,VTypeI)> func,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
        Matrix<VTypeO> rsl(lhs.rowLength(),lhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<rhs.colLength();++col){
                rsl(row,col)=func(lhs(row,col),rhs(row,col));
            }
        }
        return rsl;
    }
}//namespace vtx