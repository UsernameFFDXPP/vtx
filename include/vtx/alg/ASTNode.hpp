#pragma once

#include<memory>
#include<cstddef>

#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Visitor.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/OperatorTraits.hpp"

namespace vtx{
    template<typename VTypeI,typename VTypeO>
    class ASTNode{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using value_type=VTypeI;
            using size_type=std::size_t;

            virtual ~ASTNode()=default;

            std::size_t rowLength() const;
            std::size_t colLength() const;
            Operator opr() const;

            virtual VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const=0;
            VTypeO operator()(std::size_t row,std::size_t col) const;

        protected:
            ASTNode();
            std::size_t rowLength_;
            std::size_t colLength_;
            Operator opr_;
        private:
    };

    template<typename VTypeI,typename VTypeO>
    class MatNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            MatNode(Operator opr,const Matrix<VTypeI> *mat);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;

        private:
            const Matrix<VTypeI> *mat_;
    };

    template<typename VTypeI,typename VTypeO>
    class NegLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            NegLikeNode(Operator opr,node_sptr node);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;

        private:
            node_sptr node_;
    };

    template<typename VTypeI,typename VTypeO>
    class AddLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            AddLikeNode(Operator opr,node_sptr lhs,node_sptr rhs);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;

        private:
            node_sptr lhs_,rhs_;
    };

    template<typename VTypeI,typename VTypeO>
    class FlipLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            FlipLikeNode(Operator opr,node_sptr node,Axis axis);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;

        private:
            node_sptr node_;
            Axis axis_;
    };

    template<typename VTypeI,typename VTypeO>
    class ConcatLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            ConcatLikeNode(Operator opr,node_sptr lhs,node_sptr rhs,Axis axis);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;
            
        private:
            node_sptr lhs_,rhs_;
            Axis axis_;
    };

    template<typename VTypeI,typename VTypeO>
    class ResizeLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            ResizeLikeNode(Operator opr,node_sptr node,std::size_t idx1,std::size_t idx2);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;
            
        private:
            node_sptr node_;
            size_type idx1_,idx2_;
    };

    template<typename VTypeI,typename VTypeO>
    class DropLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            DropLikeNode(Operator opr,node_sptr node,Axis axis,std::size_t idx);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            size_type idx_;
    };

    template<typename VTypeI,typename VTypeO>
    class SwapLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            SwapLikeNode(Operator opr,node_sptr node,Axis axis,std::size_t arg1,std::size_t arg2);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            VTypeI idx1_,idx2_;
    };

    template<typename VTypeI,typename VTypeO>
    class EwiseLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            EwiseLikeNode(Operator opr,node_sptr node,VTypeI arg);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;

        private:
            node_sptr node_;
            VTypeI arg_;
    };

    template<typename VTypeI,typename VTypeO>
    class QuantileLikeNode:public ASTNode<VTypeI,VTypeO>{
        friend class EvalVisitor<VTypeI,VTypeO>;
        public:
            using size_type=std::size_t;
            using node_sptr=std::shared_ptr<ASTNode<VTypeI,VTypeO>>;
            QuantileLikeNode(Operator opr,node_sptr node,Axis axis,VTypeI arg);

            VTypeO accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const override;
            
        private:
            node_sptr node_;
            Axis axis_;
            VTypeI arg_;
    };
}//namespace vtx

#include"vtx/alg/ASTNode.tpp"