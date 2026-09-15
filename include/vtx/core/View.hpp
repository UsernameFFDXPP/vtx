#pragma once

#include<memory>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/ASTNode.hpp"
#include"vtx/core/Visitor.hpp"

namespace vtx{
    template<typename VType>
    class Expression{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            Expression(const Matrix<VType> *mat);
            Expression(Operation opr,const Expression<VType> &expr);
            Expression(Operation opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr);

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

    template<typename VType>
    class View{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            View()=default;
            explicit View(const Matrix<value_type> *mat);
            View(Operation opr,const View<value_type> &view);
            View(Operation opr,const View<value_type> &lhs,const View<value_type> &rhs);

            value_type operator()(size_type row,size_type col) const;

            Matrix<value_type> eval() const;

        private:
            Expression<value_type> expr_;
    };
}

#include"vtx/core/View.tpp"