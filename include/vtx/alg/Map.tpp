#include"vtx/alg/Map.hpp"

namespace vtx{
    namespace map{
        template<typename VTypeI,typename VTypeO>
        void mapUnaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    if(opr==OprArithm::Neg){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Neg>())
                            rsl(row,col)=algNeg(mat(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseInv){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseInv>())
                            rsl(row,col)=algEwiseInv(mat(row,col));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }

        template<typename VTypeI,typename VTypeO>
        void mapBinaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    if(opr==OprArithm::Add){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Add>())
                            rsl(row,col)=algAdd(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::Sub){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Sub>())
                            rsl(row,col)=algSub(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Equal){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Equal>())
                            rsl(row,col)=algEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Greater){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Greater>())
                            rsl(row,col)=algGreater(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::GreaterEqual){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::GreaterEqual>())
                            rsl(row,col)=algGreaterEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Less){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Less>())
                            rsl(row,col)=algLess(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::LessEqual){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::LessEqual>())
                            rsl(row,col)=algLessEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::NotEqual){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::NotEqual>())
                            rsl(row,col)=algNotEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    if(opr==OprArithm::Add){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Add>())
                            rsl(row,col)=algAdd(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::Sub){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Sub>())
                            rsl(row,col)=algSub(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const VTypeI &arg){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const VTypeI &arg,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }

        template<typename VTypeI,typename VTypeO>
        void mapReduction(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VTypeI>> tempView(&mat,Axis::Row,row);
                    if(opr==OprReduction::Sum){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Sum>())
                            rsl(row,0)=algSum(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Max){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Max>())
                            rsl(row,0)=algMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Min){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Min>())
                            rsl(row,0)=algMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMax){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMax>())
                            rsl(row,0)=algArgMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMin){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMin>())
                            rsl(row,0)=algArgMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Mean){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Mean>())
                            rsl(row,0)=algMean(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Variance){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Variance>())
                            rsl(row,0)=algVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::SampleVariance){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::SampleVariance>())
                            rsl(row,0)=algSampleVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Median){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Median>())
                            rsl(row,0)=algMedian(tempView);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.colLength();++col){
                    View<Matrix<VTypeI>> tempView(&mat,Axis::Col,col);
                    if(opr==OprReduction::Sum){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Sum>())
                            rsl(0,col)=algSum(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Max){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Max>())
                            rsl(0,col)=algMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Min){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Min>())
                            rsl(0,col)=algMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMax){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMax>())
                            rsl(0,col)=algArgMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMin){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMin>())
                            rsl(0,col)=algArgMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Mean){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Mean>())
                            rsl(0,col)=algMean(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Variance){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Variance>())
                            rsl(0,col)=algVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::SampleVariance){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::SampleVariance>())
                            rsl(0,col)=algSampleVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Median){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Median>())
                            rsl(0,col)=algMedian(tempView);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::None){
                View<Matrix<VTypeI>> tempView(&mat,Axis::None);
                if(opr==OprReduction::Sum){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Sum>())
                        rsl(0,0)=algSum(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::Max){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Max>())
                        rsl(0,0)=algMax(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::Min){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Min>())
                        rsl(0,0)=algMin(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::ArgMax){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMax>())
                        rsl(0,0)=algArgMax(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::ArgMin){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMin>())
                        rsl(0,0)=algArgMin(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Mean){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Mean>())
                        rsl(0,0)=algMean(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Variance){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Variance>())
                        rsl(0,0)=algVariance(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::SampleVariance){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::SampleVariance>())
                        rsl(0,0)=algSampleVariance(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Median){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Median>())
                        rsl(0,0)=algMedian(tempView);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
            }else /*Axis Error*/;
        }

        template<typename VTypeI,typename VTypeO>
        void mapQuantile(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis,double q){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VTypeI>> tempView(&mat,Axis::Row,row);
                    if(opr==OprStatistics::Quantile){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>())
                            rsl(row,0)=algQuantile(tempView,q);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.colLength();++col){
                    View<Matrix<VTypeI>> tempView(&mat,Axis::Col,col);
                    if(opr==OprStatistics::Quantile){
                        if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>())
                            rsl(0,col)=algQuantile(tempView,q);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::None){
                View<Matrix<VTypeI>> tempView(&mat,Axis::None);
                if(opr==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>())
                        rsl(0,0)=algQuantile(tempView,q);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
            }else /*Axis Error*/;
        }
    }//namespace arithm_map
}//namespace vtx