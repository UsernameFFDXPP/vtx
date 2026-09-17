#pragma once

#include<memory>
#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Visitor.hpp"
#include"vtx/core/Operation.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType>
    class ASTNode{
        friend class EvalVisitor<VType>;
        public:
            using value_type=VType;
            using size_type=std::size_t;

            virtual ~ASTNode()=default;

            size_type rowLength() const;
            size_type colLength() const;
            Operation opr() const;

            virtual VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const=0;

        protected:
            ASTNode();
            size_type rowLength_;
            size_type colLength_;
            Operation opr_;
        private:
    };

    template<typename VType>
    class MatNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            MatNode(Operation opr,const Matrix<VType> *mat);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            const Matrix<VType> *mat_;
    };

    template<typename VType>
    class UnaryNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            UnaryNode(Operation opr,node_sptr node);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
    };

    template<typename VType>
    class BinaryNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            BinaryNode(Operation opr,node_sptr lhs,node_sptr rhs);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr lhs_;
            node_sptr rhs_;
    };

    template<typename VType>
    class ArgNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            ArgNode(Operation opr,node_sptr node,VType arg);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
            VType arg_;
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