#pragma once

#include<memory>
#include"vtx/core/Matrix.hpp"
#include"vtx/alg/ASTNode.hpp"
#include"vtx/alg/Visitor.hpp"

namespace vtx{
    template<typename VType>
    class Expression{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            Expression(const Matrix<VType> *mat);
            
            Expression(Operator opr,const Expression<VType> &expr);
            Expression(Operator opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr);
            Expression(Operator opr,const Expression<VType> &expr,Axis axis);
            Expression(Operator opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr,Axis axis);
            Expression(Operator opr,const Expression<VType> &expr,std::size_t idx1,std::size_t idx2);
            Expression(Operator opr,const Expression<VType> &expr,Axis axis,std::size_t idx);
            Expression(Operator opr,const Expression<VType> &expr,Axis axis,std::size_t idx1,std::size_t idx2);
            Expression(Operator opr,const Expression<VType> &expr,const VType &arg);
            Expression(Operator opr,const Expression<VType> &expr,Axis axis,const VType &arg);

            std::size_t rowLength() const;
            std::size_t colLength() const;
            Matrix<VType> eval() const;
            VType evalAt(std::size_t row,std::size_t col) const;
            VType operator()(std::size_t row,std::size_t col) const;

        private:
            std::shared_ptr<ASTNode<VType>> root_=nullptr;
    };
}//namespace vtx

#include"vtx/alg/Expression.tpp"