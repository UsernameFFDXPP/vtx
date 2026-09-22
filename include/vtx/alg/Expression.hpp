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
            Expression(Operation opr,const Expression<VType> &expr);
            Expression(Operation opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr);
            Expression(Operation opr,const Expression<VType> &expr,const VType &arg);

            size_type rowLength() const;
            size_type colLength() const;
            Matrix<value_type> eval() const;
            value_type evalAt(size_type row,size_type col) const;

            bool useTempRsl() const;
            void setTempRsl(bool set);
            void clearTempRsl();

        private:
            std::shared_ptr<ASTNode<value_type>> root_=nullptr;
            bool useTempRsl_=false;
            Matrix<value_type> tempRsl_;
            Matrix<bool> tempRslMask_;
    };
}//namespace vtx

#include"vtx/alg/Expression.tpp"