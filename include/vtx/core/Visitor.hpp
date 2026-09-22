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
                        if constexpr(type_opr_traits::isNegAble<VType>::value)
                            return arithmNeg(val);
                        else /*Operation Error*/;break;
                    case Operation::EwiseInv:
                        if constexpr(type_opr_traits::isDivAble<VType,VType>::value)
                            return arithmEwiseInv(val);
                        else /*Operation Error*/;break;
                    default:
                        /*Operation Error*/
                        break;
                }
                return VType{};
            }
            VType visit(const BinaryNode<VType> &node,size_type row,size_type col) const override{
                switch(node.opr()){
                    case Operation::MatMul:{
                        if constexpr(type_opr_traits::isMulAble<VType,VType>::value){
                            View<ASTNode<VType>> lhs(node.lhs_.get(),Axis::Row,row);
                            View<ASTNode<VType>> rhs(node.rhs_.get(),Axis::Col,col);
                            return arithmMatMul(lhs,rhs);
                        }else /*Operation Error*/;break;
                    }
                    case Operation::Add:{
                        if constexpr(type_opr_traits::isAddAble<VType,VType>::value){
                            VType lhs=node.lhs_->accept(*this,row,col);
                            VType rhs=node.rhs_->accept(*this,row,col);
                            return arithmAdd(lhs,rhs);
                        }else /*Operation Error*/;break;
                    }
                    case Operation::Sub:{
                        if constexpr(type_opr_traits::isSubAble<VType,VType>::value){
                            VType lhs=node.lhs_->accept(*this,row,col);
                            VType rhs=node.rhs_->accept(*this,row,col);
                            return arithmSub(lhs,rhs);
                        }else /*Operation Error*/;break;
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
                        if constexpr(type_opr_traits::isMulAble<VType,VType>::value)
                            return arithmEwiseMul(val,arg);
                        else /*Operation Error*/;break;
                    case Operation::EwiseDiv:
                        if constexpr(type_opr_traits::isDivAble<VType,VType>::value)
                            return arithmEwiseDiv(val,arg);
                        else /*Operation Error*/;break;
                    case Operation::EwiseMod:
                        if constexpr(type_opr_traits::isModAble<VType,VType>::value)
                            return arithmEwiseMod(val,arg);
                        else /*Operation Error*/;break;
                    default:
                        /*Operation Error*/
                        break;
                }
                return VType{};
            }
    };
}//namespace vtx