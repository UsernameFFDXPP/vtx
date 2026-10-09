#include"vtx/alg/Map.hpp"

namespace vtx{
    namespace map{
        template<typename VType,typename VTypeR>
        void mapUnaryEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    if(opr==OprArithm::Neg){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::Neg>())
                            rsl(row,col)=algNeg(mat(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseInv){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseInv>())
                            rsl(row,col)=algEwiseInv(mat(row,col));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }

        template<typename VType,typename VTypeR>
        void mapBinaryEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    if(opr==OprArithm::Add){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::Add>())
                            rsl(row,col)=algAdd(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::Sub){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::Sub>())
                            rsl(row,col)=algSub(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Equal){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::Equal>())
                            rsl(row,col)=algEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Greater){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::Greater>())
                            rsl(row,col)=algGreater(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::GreaterEqual){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::GreaterEqual>())
                            rsl(row,col)=algGreaterEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::Less){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::Less>())
                            rsl(row,col)=algLess(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::LessEqual){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::LessEqual>())
                            rsl(row,col)=algLessEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else if(opr==OprCompare::NotEqual){
                        if constexpr(opr_traits::getOprDemand<VType,OprCompare::NotEqual>())
                            rsl(row,col)=algNotEqual(lhs(row,col),rhs(row,col));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    if(opr==OprArithm::Add){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::Add>())
                            rsl(row,col)=algAdd(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::Sub){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::Sub>())
                            rsl(row,col)=algSub(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(lhs(lrow,lcol),rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const VType &arg){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                    if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(lhs(lrow,lcol),arg);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const VType &arg,const Matrix<VType> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row){
                for(std::size_t col=0;col<rsl.colLength();++col){
                    std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                    if(opr==OprArithm::EwiseMul){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMul>())
                            rsl(row,col)=algEwiseMul(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseDiv){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseDiv>())
                            rsl(row,col)=algEwiseDiv(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else if(opr==OprArithm::EwiseMod){
                        if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseMod>())
                            rsl(row,col)=algEwiseMod(arg,rhs(rrow,rcol));
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }
        }

        template<typename VType,typename VTypeR>
        void mapReduction(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat,Axis axis){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VType>> tempView(&mat,Axis::Row,row);
                    if(opr==OprReduction::Sum){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                            rsl(row,0)=algSum(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Max){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                            rsl(row,0)=algMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Min){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                            rsl(row,0)=algMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMax){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                            rsl(row,0)=algArgMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMin){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                            rsl(row,0)=algArgMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Mean){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Mean>())
                            rsl(row,0)=algMean(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Variance){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Variance>())
                            rsl(row,0)=algVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::SampleVariance){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::SampleVariance>())
                            rsl(row,0)=algSampleVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Median){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Median>())
                            rsl(row,0)=algMedian(tempView);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.colLength();++col){
                    View<Matrix<VType>> tempView(&mat,Axis::Col,col);
                    if(opr==OprReduction::Sum){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                            rsl(0,col)=algSum(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Max){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                            rsl(0,col)=algMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::Min){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                            rsl(0,col)=algMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMax){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                            rsl(0,col)=algArgMax(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprReduction::ArgMin){
                        if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                            rsl(0,col)=algArgMin(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Mean){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Mean>())
                            rsl(0,col)=algMean(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Variance){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Variance>())
                            rsl(0,col)=algVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::SampleVariance){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::SampleVariance>())
                            rsl(0,col)=algSampleVariance(tempView);
                        else /*Operator Error*/;
                    }else if(opr==OprStatistics::Median){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Median>())
                            rsl(0,col)=algMedian(tempView);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::None){
                View<Matrix<VType>> tempView(&mat,Axis::None);
                if(opr==OprReduction::Sum){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>())
                        rsl(0,0)=algSum(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::Max){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>())
                        rsl(0,0)=algMax(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::Min){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>())
                        rsl(0,0)=algMin(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::ArgMax){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>())
                        rsl(0,0)=algArgMax(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprReduction::ArgMin){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>())
                        rsl(0,0)=algArgMin(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Mean){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Mean>())
                        rsl(0,0)=algMean(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Variance){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Variance>())
                        rsl(0,0)=algVariance(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::SampleVariance){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::SampleVariance>())
                        rsl(0,0)=algSampleVariance(tempView);
                    else /*Operator Error*/;
                }else if(opr==OprStatistics::Median){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Median>())
                        rsl(0,0)=algMedian(tempView);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
            }else /*Axis Error*/;
        }

        template<typename VType,typename VTypeR>
        void mapQuantile(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat,Axis axis,double q){
            if(axis==Axis::Row){
                for(std::size_t row=0;row<mat.rowLength();++row){
                    View<Matrix<VType>> tempView(&mat,Axis::Row,row);
                    if(opr==OprStatistics::Quantile){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Quantile>())
                            rsl(row,0)=algQuantile(tempView,q);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::Col){
                for(std::size_t col=0;col<mat.colLength();++col){
                    View<Matrix<VType>> tempView(&mat,Axis::Col,col);
                    if(opr==OprStatistics::Quantile){
                        if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Quantile>())
                            rsl(0,col)=algQuantile(tempView,q);
                        else /*Operator Error*/;
                    }else /*Operator Error*/;
                }
            }else if(axis==Axis::None){
                View<Matrix<VType>> tempView(&mat,Axis::None);
                if(opr==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Quantile>())
                        rsl(0,0)=algQuantile(tempView,q);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
            }else /*Axis Error*/;
        }
    }//namespace arithm_map
}//namespace vtx