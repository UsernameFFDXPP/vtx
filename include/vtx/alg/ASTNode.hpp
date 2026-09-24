#pragma once

#include<memory>
#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Visitor.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    template<typename VType>
    class ASTNode{
        friend class EvalVisitor<VType>;
        public:
            using value_type=VType;
            using size_type=std::size_t;

            virtual ~ASTNode()=default;

            std::size_t rowLength() const;
            std::size_t colLength() const;
            Operator opr() const;

            virtual VType accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const=0;
            VType operator()(std::size_t row,std::size_t col) const;

        protected:
            ASTNode();
            std::size_t rowLength_;
            std::size_t colLength_;
            Operator opr_;
        private:
    };

    template<typename VType>
    class MatNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            MatNode(Operator opr,const Matrix<VType> *mat);

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
            UnaryNode(Operator opr,node_sptr node);

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
            BinaryNode(Operator opr,node_sptr lhs,node_sptr rhs);

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
            ArgNode(Operator opr,node_sptr node,VType arg);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
            VType arg_;
    };

    template<typename VType>
    class ReductionNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            ReductionNode(Operator opr,node_sptr node,Axis axis);
            VType evalAt(size_type row,size_type col) const override;
        private:
            node_sptr node_;
            Axis axis_;
    };
    
}//namespace vtx

#include"vtx/alg/ASTNode.tpp"