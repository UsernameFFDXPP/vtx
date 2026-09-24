#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/core/View.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"
#include"vtx/alg/arithm/Arithm.hpp"
#include"vtx/alg/reduction/Reduction.hpp"
#include"vtx/alg/statistics/Statistics.hpp"

namespace vtx{
    namespace map{
        template<typename VType>
        void mapUnaryEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &mat);

        template<typename VType>
        void mapBinaryEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs);
        
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs);
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const Matrix<VType> &lhs,const VType &arg);
        template<typename VType>
        void mapBroadcastEwise(Matrix<VType> &rsl,OprArithm opr,const VType &arg,const Matrix<VType> &rhs);

        template<typename VType>
        void mapReduction(Matrix<VType> &rsl,OprReduction opr,const Matrix<VType> &mat,Axis axis);
    }//namespace arithm_map
}//namespace vtx

#include"vtx/alg/Map.tpp"