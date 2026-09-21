#pragma once

#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Operation.hpp"
#include"vtx/core/Axis.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    template<typename VType> class View;
    template<typename VType> class ASTNode;
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
                switch(node.opr()){
                    case Operation::Neg:
                    case Operation::EwiseInv:{
                        VType val=node.node_->accept(*this,row,col);
                        return unaryEwiseArithm(node.opr(),val);
                    }
                    default:{
                        /*Operation Error*/
                    }
                }
                return VType{};
            }
            VType visit(const BinaryNode<VType> &node,size_type row,size_type col) const override{
                switch(node.opr()){
                    case Operation::MatMul:{
                        View<ASTNode<VType>> lhs(node.lhs_.get(),Axis::Row,row);
                        View<ASTNode<VType>> rhs(node.rhs_.get(),Axis::Col,col);
                        return matMulArithm(lhs,rhs);
                    }
                    case Operation::Add:
                    case Operation::Sub:{
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return binaryEwiseArithm(node.opr(),lhs,rhs);
                    }
                    default:{
                        /*Operation Error*/
                    }
                }
                return VType{};
            }
            VType visit(const ArgNode<VType> &node,size_type row,size_type col) const override{
                switch(node.opr()){
                    case Operation::EwiseMul:
                    case Operation::EwiseDiv:
                    case Operation::EwiseMod:{
                        VType val=node.node_->accept(*this,row,col);
                        VType arg=node.arg_;
                        return binaryEwiseArithm(node.opr(),val,arg);
                    }
                    default:{
                        /*Operation Error*/
                    }
                }
                return VType{};
            }
    };
}