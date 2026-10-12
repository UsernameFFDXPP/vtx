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
        template<typename VTypeI,typename VTypeO>
        void mapUnaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat);

        template<typename VTypeI,typename VTypeO>
        void mapBinaryEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs);
        
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const Matrix<VTypeI> &rhs);
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &lhs,const VTypeI &arg);
        template<typename VTypeI,typename VTypeO>
        void mapBroadcastEwise(Matrix<VTypeO> &rsl,Operator opr,const VTypeI &arg,const Matrix<VTypeI> &rhs);

        template<typename VTypeI,typename VTypeO>
        void mapReduction(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis);
        template<typename VTypeI,typename VTypeO>
        void mapQuantile(Matrix<VTypeO> &rsl,Operator opr,const Matrix<VTypeI> &mat,Axis axis,double q);
    }//namespace arithm_map
}//namespace vtx

#include"vtx/alg/Map.tpp"