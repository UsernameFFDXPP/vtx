#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    namespace arithm_map{
        template<typename VType>
        void mapUnaryEwise(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &mat){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    switch(opr){
                        case Operation::Neg:
                            rsl(row,col)=arithmNeg(mat(row,col));
                            break;
                        case Operation::EwiseInv:
                            rsl(row,col)=arithmEwiseInv(mat(row,col));
                            break;
                        default:
                            /*Operation Error*/
                            break;
                    }
                }
            }
        }

        template<typename VType>
        void mapBinaryEwise(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    switch(opr){
                        case Operation::Add:
                            rsl(row,col)=arithmAdd(lhs(row,col),rhs(row,col));
                            break;
                        case Operation::Sub:
                            rsl(row,col)=arithmSub(lhs(row,col),rhs(row,col));
                            break;
                        default:
                            /*Operation Error*/
                            break;
                    }
                }
            }
        }
        
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    switch(opr){
                        case Operation::Add:
                            rsl(row,col)=arithmAdd(lhs(lrow,lcol),rhs(rrow,rcol));
                            break;
                        case Operation::Sub:
                            rsl(row,col)=arithmSub(lhs(lrow,lcol),rhs(rrow,rcol));
                            break;
                        default:
                            /*Operation Error*/
                            break;
                    }
                }
            }
        }
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,Operation opr,const Matrix<VType> &lhs,const VType &arg){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    switch(opr){
                        case Operation::EwiseMul:
                            rsl(row,col)=arithmEwiseMul(lhs(lrow,lcol),arg);
                            break;
                        case Operation::EwiseDiv:
                            rsl(row,col)=arithmEwiseDiv(lhs(lrow,lcol),arg);
                            break;
                        case Operation::EwiseMod:
                            rsl(row,col)=arithmEwiseMod(lhs(lrow,lcol),arg);
                            break;
                        default:
                            /*Operation Error*/
                            break;
                    }
                }
            }
        }
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,Operation opr,const VType &arg,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    switch(opr){
                        case Operation::EwiseMul:
                            rsl(row,col)=arithmEwiseMul(arg,rhs(rrow,rcol));
                            break;
                        case Operation::EwiseDiv:
                            rsl(row,col)=arithmEwiseDiv(arg,rhs(rrow,rcol));
                            break;
                        case Operation::EwiseMod:
                            rsl(row,col)=arithmEwiseMod(arg,rhs(rrow,rcol));
                            break;
                        default:
                            /*Operation Error*/
                            break;
                    }
                }
            }
        }
    }

    /*Neg*/
    template<typename VType>
    Matrix<VType> neg(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapUnaryEwise(rsl,Operation::Neg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &neg_(Matrix<VType> &mat){
        arithm_map::mapUnaryEwise(mat,Operation::Neg,mat);
        return mat;
    }
    /*EwiseInv*/
    template<typename VType>
    Matrix<VType> ewiseInv(const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapUnaryEwise(rsl,Operation::EwiseInv,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseInv_(Matrix<VType> &mat){
        arithm_map::mapUnaryEwise(mat,Operation::EwiseInv,mat);
        return mat;
    }
    /*EwiseMul*/
    template<typename VType>
    Matrix<VType> ewiseMul(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseMul,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMul_(Matrix<VType> &mat,const VType &arg){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseMul,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseMul(VType arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseMul,mat,arg);
        return rsl;
    }
        template<typename VType>
    Matrix<VType> &ewiseMul_(VType arg,Matrix<VType> &mat){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseMul,mat,arg);
        return mat;
    }
    /*EwiseDiv*/
    template<typename VType>
    Matrix<VType> ewiseDiv(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseDiv,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseDiv_(Matrix<VType> &mat,const VType &arg){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseDiv,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseDiv(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseDiv,arg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseDiv_(const VType &arg,Matrix<VType> &mat){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseDiv,arg,mat);
        return mat;
    }
    /*EwiseMod*/
    template<typename VType>
    Matrix<VType> ewiseMod(const Matrix<VType> &mat,const VType &arg){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseMod,mat,arg);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMod_(Matrix<VType> &mat,const VType &arg){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseMod,mat,arg);
        return mat;
    }
    template<typename VType>
    Matrix<VType> ewiseMod(const VType &arg,const Matrix<VType> &mat){
        Matrix<VType> rsl(mat.rowLength(),mat.colLength());
        arithm_map::mapBroadcastEwise(rsl,Operation::EwiseMod,arg,mat);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &ewiseMod_(const VType &arg,Matrix<VType> &mat){
        arithm_map::mapBroadcastEwise(mat,Operation::EwiseMod,arg,mat);
        return mat;
    }
    /*Add*/
    template<typename VType>
    Matrix<VType> add(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        arithm_map::mapBinaryEwise(rsl,Operation::Add,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &add_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        arithm_map::mapBinaryEwise(lhs,Operation::Add,lhs,rhs);
        return lhs;
    }
    /*Sub*/
    template<typename VType>
    Matrix<VType> sub(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),lhs.colLength());
        arithm_map::mapBinaryEwise(rsl,Operation::Sub,lhs,rhs);
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &sub_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        arithm_map::mapBinaryEwise(lhs,Operation::Sub,lhs,rhs);
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
    Matrix<VType> matMul(const Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),rhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<lhs.rowLength();++col){
                rsl(row,col)=arithmMatMul(View<Matrix<VType>>(&lhs,Axis::Row,row),View<Matrix<VType>>(&rhs,Axis::Col,col));
            }
        }
        return rsl;
    }
    template<typename VType>
    Matrix<VType> &matMul_(Matrix<VType> &lhs,const Matrix<VType> &rhs){
        Matrix<VType> rsl(lhs.rowLength(),rhs.colLength());
        for(std::size_t row=0;row<lhs.rowLength();++row){
            for(std::size_t col=0;col<lhs.rowLength();++col){
                rsl(row,col)=arithmMatMul(View<Matrix<VType>>(&lhs,Axis::Row,row),View<Matrix<VType>>(&rhs,Axis::Col,col));
            }
        }
        lhs=std::move(rsl);
        return lhs;
    }
}