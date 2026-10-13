#pragma once

#include<memory>
#include"vtx/core/Matrix.hpp"
#include"vtx/alg/ASTNode.hpp"
#include"vtx/alg/Visitor.hpp"

namespace vtx{
    template<typename VTypeO>
    class Expression{
        template<typename> friend class Expression;
        public:
            using value_type=VTypeO;
            using size_type=std::size_t;

            Expression(const Matrix<VTypeO> *mat);
            
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &lexpr,const Expression<VTypeI> &rexpr);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &lexpr,const Expression<VTypeI> &rexpr,Axis axis);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,std::size_t idx1,std::size_t idx2);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,std::size_t idx);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,std::size_t idx1,std::size_t idx2);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,const VTypeI &arg);
            template<typename VTypeI>
            Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,double arg);

            std::size_t rowLength() const;
            std::size_t colLength() const;
            Matrix<VTypeO> eval() const;
            VTypeO evalAt(std::size_t row,std::size_t col) const;
            VTypeO operator()(std::size_t row,std::size_t col) const;

        private:
            std::shared_ptr<NodeBase<VTypeO>> root_=nullptr;
    };
}//namespace vtx

#include"vtx/alg/Expression.tpp"