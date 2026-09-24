#include"vtx/alg/Map.hpp"

namespace vtx{
    namespace map{
        template<typename VType>
        void mapUnaryEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &mat){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    switch(opr){
                        case OprArithm::Neg:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::Neg>())
                                rsl(row,col)=arithmNeg(mat(row,col));
                            else /*Operator Error*/;break;
                        case OprArithm::EwiseInv:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseInv>())
                                rsl(row,col)=arithmEwiseInv(mat(row,col));
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }
        }

        template<typename VType>
        void mapBinaryEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    switch(opr){
                        case OprArithm::Add:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::Add>())
                                rsl(row,col)=arithmAdd(lhs(row,col),rhs(row,col));
                            else /*Operator Error*/;break;
                        case OprArithm::Sub:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::Sub>())
                                rsl(row,col)=arithmSub(lhs(row,col),rhs(row,col));
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }
        }
        
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    switch(opr){
                        case OprArithm::Add:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::Add>())
                                rsl(row,col)=arithmAdd(lhs(lrow,lcol),rhs(rrow,rcol));
                            else /*Operator Error*/;break;
                        case OprArithm::Sub:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::Sub>())
                                rsl(row,col)=arithmSub(lhs(lrow,lcol),rhs(rrow,rcol));
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }
        }
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const VType &arg){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    switch(opr){
                        case OprArithm::EwiseMul:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMul>())
                                rsl(row,col)=arithmEwiseMul(lhs(lrow,lcol),arg);
                            else /*Operator Error*/;break;
                        case OprArithm::EwiseDiv:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>())
                                rsl(row,col)=arithmEwiseDiv(lhs(lrow,lcol),arg);
                            else /*Operator Error*/;break;
                        case OprArithm::EwiseMod:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMod>())
                                rsl(row,col)=arithmEwiseMod(lhs(lrow,lcol),arg);
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }
        }
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const VType &arg,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    switch(opr){
                        case OprArithm::EwiseMul:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMul>())
                                rsl(row,col)=arithmEwiseMul(arg,rhs(rrow,rcol));
                            else /*Operator Error*/;break;
                        case OprArithm::EwiseDiv:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>())
                                rsl(row,col)=arithmEwiseDiv(arg,rhs(rrow,rcol));
                            else /*Operator Error*/;break;
                        case OprArithm::EwiseMod:
                            if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMod>())
                                rsl(row,col)=arithmEwiseMod(arg,rhs(rrow,rcol));
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }
        }

        template<typename VType>
        void mapReduction(Matrix<VType> &rsl,OprReduction opr,const Matrix<VType> &mat,Axis axis){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VType>> tempView(&mat,Axis::Row,row);
                    switch(opr){
                        case OprReduction::Sum:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                                rsl(row,0)=arithmSum(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::Max:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                                rsl(row,0)=arithmMax(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::Min:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                                rsl(row,0)=arithmMin(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::ArgMax:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                                rsl(row,0)=arithmArgMax(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::ArgMin:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                                rsl(row,0)=arithmArgMin(tempView);
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.rowLength();++col){
                    View<Matrix<VType>> tempView(&mat,Axis::Col,col);
                    switch(opr){
                        case OprReduction::Sum:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                                rsl(0,col)=arithmSum(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::Max:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                                rsl(0,col)=arithmMax(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::Min:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                                rsl(0,col)=arithmMin(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::ArgMax:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                                rsl(0,col)=arithmArgMax(tempView);
                            else /*Operator Error*/;break;
                        case OprReduction::ArgMin:
                            if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                                rsl(0,col)=arithmArgMin(tempView);
                            else /*Operator Error*/;break;
                        default:
                            /*Operator Error*/;break;
                    }
                }
            }else if(axis==Axis::None){
                View<Matrix<VType>> tempView(&mat,Axis::None);
                switch(opr){
                    case OprReduction::Sum:
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                            rsl(0,0)=arithmSum(tempView);
                        else /*Operator Error*/;break;
                    case OprReduction::Max:
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                            rsl(0,0)=arithmMax(tempView);
                        else /*Operator Error*/;break;
                    case OprReduction::Min:
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                            rsl(0,0)=arithmMin(tempView);
                        else /*Operator Error*/;break;
                    case OprReduction::ArgMax:
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                            rsl(0,0)=arithmArgMax(tempView);
                        else /*Operator Error*/;break;
                    case OprReduction::ArgMin:
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                            rsl(0,0)=arithmArgMin(tempView);
                        else /*Operator Error*/;break;
                    default:
                        /*Operator Error*/;break;
                }
            }else /*Axis Error*/;
        }
    }//namespace arithm_map
}//namespace vtx