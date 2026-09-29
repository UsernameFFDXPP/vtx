#pragma once

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/core/View.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"
#include"vtx/alg/arithm/Arithm.hpp"
#include"vtx/alg/compare/Compare.hpp"
#include"vtx/alg/reduction/Reduction.hpp"
#include"vtx/alg/statistics/Statistics.hpp"

namespace vtx{
    namespace map{
        template<typename VType,typename VTypeR>
        void mapUnaryEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat);

        template<typename VType,typename VTypeR>
        void mapBinaryEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs);
        
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const Matrix<VType> &rhs);
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &lhs,const VType &arg);
        template<typename VType,typename VTypeR>
        void mapBroadcastEwise(Matrix<VTypeR> &rsl,Operator opr,const VType &arg,const Matrix<VType> &rhs);

        template<typename VType,typename VTypeR>
        void mapReduction(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat,Axis axis);
        template<typename VType,typename VTypeR>
        void mapQuantile(Matrix<VTypeR> &rsl,Operator opr,const Matrix<VType> &mat,Axis axis,double q);
    }//namespace arithm_map
}//namespace vtx

#include"vtx/alg/Map.tpp"