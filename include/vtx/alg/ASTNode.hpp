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
    class NegLikeNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            NegLikeNode(Operator opr,node_sptr node);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
    };

    template<typename VType>
    class AddLikeNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            AddLikeNode(Operator opr,node_sptr lhs,node_sptr rhs);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr lhs_,rhs_;
    };

    template<typename VType>
    class FlipLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            FlipLikeNode(Operator opr,node_sptr node,Axis axis);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
            Axis axis_;
    };

    template<typename VType>
    class ConcatLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            ConcatLikeNode(Operator opr,node_sptr lhs,node_sptr rhs,Axis axis);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;
            
        private:
            node_sptr lhs_,rhs_;
            Axis axis_;
    };

    template<typename VType>
    class ResizeLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            ResizeLikeNode(Operator opr,node_sptr node,size_type idx1,size_type idx2);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;
            
        private:
            node_sptr node_;
            size_type idx1_,idx2_;
    };

    template<typename VType>
    class DropLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            DropLikeNode(Operator opr,node_sptr node,Axis axis,size_type idx);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            size_type idx_;
    };

    template<typename VType>
    class SwapLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            SwapLikeNode(Operator opr,node_sptr node,Axis axis,size_type arg1,size_type arg2);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            VType idx1_,idx2_;
    };

    template<typename VType>
    class EwiseLikeNode:public ASTNode<VType>{
        friend class EvalVisitor<VType>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            EwiseLikeNode(Operator opr,node_sptr node,VType arg);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;

        private:
            node_sptr node_;
            VType arg_;
    };

    template<typename VType>
    class QuantileLikeNode:public ASTNode<VType>{
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VType>>;
            QuantileLikeNode(Operator opr,node_sptr node,Axis axis,VType arg);

            VType accept(const NodeVisitor<VType> &visitor,size_type row,size_type col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            VType arg_;
    };
}//namespace vtx

#include"vtx/alg/ASTNode.tpp"