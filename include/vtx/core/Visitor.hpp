#pragma once

#include<cstddef>

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
                VType val=node.node_->accept(*this,row,col);
                switch(node.opr()){
                    case Operation::Neg:
                        return arithmNeg(val);
                    case Operation::EwiseInv:
                        return arithmEwiseInv(val);
                    default:
                        /*Operation Error*/
                        break;
                }
                return VType{};
            }
            VType visit(const BinaryNode<VType> &node,size_type row,size_type col) const override{
                switch(node.opr()){
                    case Operation::MatMul:{
                        View<ASTNode<VType>> lhs(node.lhs_.get(),Axis::Row,row);
                        View<ASTNode<VType>> rhs(node.rhs_.get(),Axis::Col,col);
                        return arithmMatMul(lhs,rhs);
                    }
                    case Operation::Add:{
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return arithmAdd(lhs,rhs);
                    }
                    case Operation::Sub:{
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return arithmSub(lhs,rhs);
                    }
                    default:
                        /*Operation Error*/
                        break;
                }
                return VType{};
            }
            VType visit(const ArgNode<VType> &node,size_type row,size_type col) const override{
                VType val=node.node_->accept(*this,row,col);
                VType arg=node.arg_;
                switch(node.opr()){
                    case Operation::EwiseMul:
                        return arithmEwiseMul(val,arg);
                    case Operation::EwiseDiv:
                        return arithmEwiseDiv(val,arg);
                    case Operation::EwiseMod:
                        return arithmEwiseMod(val,arg);
                    default:
                        /*Operation Error*/
                        break;
                }
                return VType{};
            }
    };
}