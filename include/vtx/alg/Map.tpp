#include"vtx/alg/Map.hpp"

#define VTX_UNARY_OPR_BCSTM_DMD(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,col)=FUNC(mat(row,col));\
        else ERR;\
    }
#define VTX_BINARY_OPR_BCSTM_DMD(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,col)=FUNC(lhs(row,col),rhs(row,col));\
        else ERR;\
    }

#define VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,col)=FUNC(lhs(lrow,lcol),rhs(rrow,rcol));\
        else ERR;\
    }
#define VTX_BROADCAST_OPR_BCSTM_DMD_ROW(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,col)=FUNC(lhs(lrow,lcol),arg);\
        else ERR;\
    }
#define VTX_BROADCAST_OPR_BCSTM_DMD_COL(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,col)=FUNC(arg,rhs(rrow,rcol));\
        else ERR;\
    }

#define VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(row,0)=FUNC(tempView);\
        else ERR;\
    }
#define VTX_REDUCTION_OPR_BCSTM_DMD_COL(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(0,col)=FUNC(tempView);\
        else ERR;\
    }
#define VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OPR,FUNC,ERR)\
    (opr==OPR){\
        if constexpr(opr_traits::getOprDemand<VTypeI,OPR>())\
            rsl(0,0)=FUNC(tempView);\
        else ERR;\
    }

namespace vtx{
    namespace map{
        template<typename VTypeI,typename VTypeO>
        void mapUnaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat){
            for(std::size_t row=0;row<rsl.rowLength();++row) for(std::size_t col=0;col<rsl.colLength();++col){
                if VTX_UNARY_OPR_BCSTM_DMD(OprArithm::Neg,algNeg,/*Operator Error*/)
                else if VTX_UNARY_OPR_BCSTM_DMD(OprArithm::EwiseInv,algEwiseInv,/*Operator Error*/)
                else /*Operator Error*/;
            }
        }

        template<typename VTypeI,typename VTypeO>
        void mapBinaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row) for(std::size_t col=0;col<rsl.colLength();++col){
                if VTX_BINARY_OPR_BCSTM_DMD(OprArithm::Add,algAdd,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprArithm::Sub,algSub,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprArithm::EwiseMul,algEwiseMul,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprArithm::EwiseDiv,algEwiseDiv,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprArithm::EwiseMod,algEwiseMod,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::Equal,algEqual,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::Greater,algGreater,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::GreaterEqual,algGreaterEqual,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::Less,algLess,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::LessEqual,algLessEqual,/*Operator Error*/)
                else if VTX_BINARY_OPR_BCSTM_DMD(OprCompare::NotEqual,algNotEqual,/*Operator Error*/)
                else /*Operator Error*/;
            }
        }
        
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row) for(std::size_t col=0;col<rsl.colLength();++col){
                std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                if VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OprArithm::Add,algAdd,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OprArithm::Sub,algSub,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OprArithm::EwiseMul,algEwiseMul,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OprArithm::EwiseDiv,algEwiseDiv,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_NONE(OprArithm::EwiseMod,algEwiseMod,/*Operator Error*/)
                else /*Operator Error*/;
            }
        }
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const VTypeI &arg){
            for(std::size_t row=0;row<rsl.rowLength();++row) for(std::size_t col=0;col<rsl.colLength();++col){
                std::size_t lrow=row%lhs.rowLength(),lcol=col%lhs.colLength();
                if VTX_BROADCAST_OPR_BCSTM_DMD_ROW(OprArithm::ScalarMul,algScalarMul,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_ROW(OprArithm::ScalarDiv,algScalarDiv,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_ROW(OprArithm::ScalarMod,algScalarMod,/*Operator Error*/)
                else /*Operator Error*/;
            }
        }
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const VTypeI &arg,const Matrix<VTypeI> &rhs){
            for(std::size_t row=0;row<rsl.rowLength();++row) for(std::size_t col=0;col<rsl.colLength();++col){
                std::size_t rrow=row%rhs.rowLength(),rcol=col%rhs.colLength();
                if VTX_BROADCAST_OPR_BCSTM_DMD_COL(OprArithm::ScalarMul,algScalarMul,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_COL(OprArithm::ScalarDiv,algScalarDiv,/*Operator Error*/)
                else if VTX_BROADCAST_OPR_BCSTM_DMD_COL(OprArithm::ScalarMod,algScalarMod,/*Operator Error*/)
                else /*Operator Error*/;
            }
        }

        template<typename VTypeI,typename VTypeO>
        void mapReduction(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis){
            if(axis==Axis::Row) for(std::size_t row=0;row<mat.rowLength();++row){
                View<Matrix<VTypeI>> tempView(&mat,Axis::Row,row);
                if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprReduction::Sum,algSum,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprReduction::Max,algMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprReduction::Min,algMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprReduction::ArgMax,algArgMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprReduction::ArgMin,algArgMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprStatistics::Mean,algMean,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprStatistics::Variance,algVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprStatistics::SampleVariance,algSampleVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_ROW(OprStatistics::Median,algMedian,/*Operator Error*/)
                else /*Operator Error*/;
            }else if(axis==Axis::Col) for(std::size_t col=0;col<mat.colLength();++col){
                View<Matrix<VTypeI>> tempView(&mat,Axis::Col,col);
                if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprReduction::Sum,algSum,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprReduction::Max,algMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprReduction::Min,algMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprReduction::ArgMax,algArgMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprReduction::ArgMin,algArgMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprStatistics::Mean,algMean,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprStatistics::Variance,algVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprStatistics::SampleVariance,algSampleVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_COL(OprStatistics::Median,algMedian,/*Operator Error*/)
                else /*Operator Error*/;
            }else if(axis==Axis::None){
                View<Matrix<VTypeI>> tempView(&mat,Axis::None);
                if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprReduction::Sum,algSum,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprReduction::Max,algMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprReduction::Min,algMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprReduction::ArgMax,algArgMax,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprReduction::ArgMin,algArgMin,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprStatistics::Mean,algMean,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprStatistics::Variance,algVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprStatistics::SampleVariance,algSampleVariance,/*Operator Error*/)
                else if VTX_REDUCTION_OPR_BCSTM_DMD_NONE(OprStatistics::Median,algMedian,/*Operator Error*/)
                else /*Operator Error*/;
            }else /*Axis Error*/;
        }

        template<typename VTypeI,typename VTypeO>
        void mapQuantile(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis,double q){
            if(axis==Axis::Row) for(std::size_t row=0;row<mat.rowLength();++row){
                View<Matrix<VTypeI>> tempView(&mat,Axis::Row,row);
                if(opr==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>())
                        rsl(row,0)=algQuantile(tempView,q);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
            }else if(axis==Axis::Col) for(std::size_t col=0;col<mat.colLength();++col){
                View<Matrix<VTypeI>> tempView(&mat,Axis::Col,col);
                if(opr==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>())
                        rsl(0,col)=algQuantile(tempView,q);
                    else /*Operator Error*/;
                }else /*Operator Error*/;
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

#undef VTX_UNARY_OPR_BCSTM_DMD
#undef VTX_BINARY_OPR_BCSTM_DMD

#undef VTX_BROADCAST_OPR_BCSTM_DMD_NONE
#undef VTX_BROADCAST_OPR_BCSTM_DMD_ROW
#undef VTX_BROADCAST_OPR_BCSTM_DMD_COL

#undef VTX_REDUCTION_OPR_BCSTM_DMD_ROW
#undef VTX_REDUCTION_OPR_BCSTM_DMD_COL
#undef VTX_REDUCTION_OPR_BCSTM_DMD_NONE