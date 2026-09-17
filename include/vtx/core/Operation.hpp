#pragma once

namespace vtx{
    enum class Operation{
            None,
        /*Mat*/
            Mat,
        /*Ewise*/
            /*1 Oprand*/
            Neg,
            EwiseInv,
            /*1 Oprand 1 Arg*/
            EwiseMul,
            EwiseDiv,
            EwiseMod,
            /*2 Oprand*/
            Add,
            Sub,
        /*NonEwise*/
            /*1 Oprand*/
            MatInv,
            Transpose,
            /*2 Oprand*/
            MatMul,
            MatDiv,
        /*Reduction*/
            /*1 Oprand 1 Axis*/
            Sum,
            Max,
            Min,
            ArgMax,
            ArgMin,
            Mean,
            Variance,
            SampleVraiance,
            Median,
            Covariance,
            Correlation,
            /*1 Oprand 1 Arg 1 Axis*/
            Quantile
        /*Reshape*/
    };
}