#pragma once

#include<variant>

namespace vtx{
    enum class OprDefault;
    enum class OprArithm;
    enum class OprCompare;
    enum class OprLayout;
    enum class OprReduction;
    enum class OprStatistics;

    using Operator=std::variant<std::monostate,
        OprDefault,
        OprArithm,
        OprCompare,
        OprLayout,
        OprReduction,
        OprStatistics
    >;

    enum class OprDefault{
        None,
        Mat,
    };
    enum class OprArithm{
        /*1 Operand*/
        Neg,
        EwiseInv,
        MatInv,
        /*1 Operand 1 Arg*/
        EwiseMul,
        EwiseDiv,
        EwiseMod,
        /*2 Operand*/
        Add,
        Sub,
        MatMul,
        MatDiv,
    };
    enum class OprCompare{
        /*2 Operand*/
        Equal,
        Greater,
        GreaterEqual,
        Less,
        LessEqual,
        NotEqual,
    };
    enum class OprLayout{
        /*1 Operand*/
        Transpose,
        /*1 Operand 1 Axis*/
        Flip,
        /*1 Operand 2 Index*/
        Reshape,
        Resize,
        /*1 Operand 1 Axis 1 Index*/
        Insert,
        Drop,
        /*1 Operand 1 Axis 2 Index*/
        Swap,
        Slice,
        /*2 Operand 1 Axis*/
        Concat,
    };
    enum class OprReduction{
        /*1 Operand 1 Axis*/
        Sum,
        Max,
        Min,
        ArgMax,
        ArgMin,
    };
    enum class OprStatistics{
        /*1 Operand*/
        Covariance,
        Correlation,
        /*1 Operand 1 Axis*/
        Mean,
        Variance,
        SampleVariance,
        Median,
        Center,
        Standardize,
        /*1 Operand 1 Axis 1 Arg*/
        Quantile,
    };

    // Node      Axis   size_t  VType
    // 1 Operand                         =NegLike
    // 2 Operand                         =AddLike
    // 1 Operand 1 Axis                  =FlipLike
    // 2 Operand 1 Axis                  =ConcatLike
    // 1 Operand        2 Index          =ResizeLike
    // 1 Operand 1 Axis 1 Index          =DropLike
    // 1 Operand 1 Axis 2 Index          =SwapLike
    // 1 Operand                1 Arg    =EwiseLike
    // 1 Operand 1 Axis         1 Arg    =QuantileLike

    inline bool operator==(const Operator &opr,OprDefault target){
        if(const auto *v=std::get_if<OprDefault>(&opr)) return *v==target;
        return false;
    }
    inline bool operator==(const Operator &opr,OprArithm target){
        if(const auto *v=std::get_if<OprArithm>(&opr)) return *v==target;
        return false;
    }
    inline bool operator==(const Operator &opr,OprCompare target){
        if(const auto *v=std::get_if<OprCompare>(&opr)) return *v==target;
        return false;
    }
    inline bool operator==(const Operator &opr,OprLayout target){
        if(const auto *v=std::get_if<OprLayout>(&opr)) return *v==target;
        return false;
    }
    inline bool operator==(const Operator &opr,OprReduction target){
        if(const auto *v=std::get_if<OprReduction>(&opr)) return *v==target;
        return false;
    }
    inline bool operator==(const Operator &opr,OprStatistics target){
        if(const auto *v=std::get_if<OprStatistics>(&opr)) return *v==target;
        return false;
    }
}//namespace vtx