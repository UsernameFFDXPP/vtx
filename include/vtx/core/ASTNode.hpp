#pragma once

#include<memory>
#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Operation.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType>
    class ASTNode{
        public:
            using size_type=std::size_t;

            virtual ~ASTNode()=default;

            virtual VType evalAt(std::size_t row,std::size_t col) const=0;
            size_type rowLength() const;
            size_type colLength() const;
        protected:
            ASTNode();
            size_type rowLength_;
            size_type colLength_;
            Operation opr_;
        private:
    };

    template<typename VType>
    class MatNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            MatNode(Operation opr,const Matrix<VType> *mat);
            VType evalAt(size_type row,size_type col) const override;
        private:
            const Matrix<VType> *mat_;
    };

    template<typename VType>
    class UnaryNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            UnaryNode(Operation opr,node_sptr node);
            VType evalAt(size_type row,size_type col) const override;
        private:
            node_sptr node_;
    };

    template<typename VType>
    class BinaryNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            BinaryNode(Operation opr,node_sptr lhs,node_sptr rhs);
            VType evalAt(size_type row,size_type col) const override;
        private:
            node_sptr lhs_;
            node_sptr rhs_;
    };
    /*
    template<typename VType>
    class ReductionNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            ReductionNode(Operation opr,node_sptr node,Axis axis);
            VType evalAt(size_type row,size_type col) const override;
        private:
            node_sptr node_;
            Axis axis_;
    };
    */
}

#include"vtx/core/ASTNode.tpp"