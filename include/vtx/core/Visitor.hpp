#pragma once

#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Operation.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    template<typename VType> class MatNode;
    template<typename VType> class UnaryNode;
    template<typename VType> class BinaryNode;
    template<typename VType> class ArgNode;

    template<typename VType>
    class NodeVisitor{
        public:
            using size_type=std::size_t;

            virtual ~NodeVisitor()=default;
            
            virtual VType visit(const MatNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const UnaryNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const BinaryNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const ArgNode<VType> &node,size_type row,size_type col) const=0;
    };

    template<typename VType>
    class EvalVisitor:public NodeVisitor<VType>{
        public:
            using size_type=std::size_t;
            
            VType visit(const MatNode<VType> &node,size_type row,size_type col) const override{
                return (*node.mat_)(row,col);
            }
            VType visit(const UnaryNode<VType> &node,size_type row,size_type col) const override{
                VType val=node.node_->accept(*this,row,col);
                return unaryEwiseArithm(node.opr(),val);
            }
            VType visit(const BinaryNode<VType> &node,size_type row,size_type col) const override{
                VType lhs=node.lhs_->accept(*this,row,col);
                VType rhs=node.rhs_->accept(*this,row,col);
                return binaryEwiseArithm(node.opr(),lhs,rhs);
            }
            VType visit(const ArgNode<VType> &node,size_type row,size_type col) const override{
                VType val=node.node_->accept(*this,row,col);
                VType arg=node.arg_;
                return binaryEwiseArithm(node.opr(),val,arg);
            }
    };
}