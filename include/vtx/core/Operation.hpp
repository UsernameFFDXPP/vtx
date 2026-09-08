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
            Sum,
            Max,
            Min,
            ArgMax,
            ArgMin,
            Mean,
            Variance,
            Mediam,
            Quantile,
            Covariance,
            Correlation
    };
}