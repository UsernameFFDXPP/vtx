#pragma once

#include<cstddef>

#include"vtx/core/Axis.hpp"

#include"vtx/core/View.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/arithm/Arithm.hpp"

namespace vtx{
    template<typename VType> class ASTNode;
    template<typename VType> class MatNode;
    template<typename VType> class NegLikeNode;
    template<typename VType> class AddLikeNode;
    template<typename VType> class EwiseLikeNode;
    
    template<typename VType> class NodeVisitor;
    template<typename VType> class EvalVisitor;

    /*
    template<typename Source,typename VType>
    class ViewLike{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            ViewLike(const Source *source,Axis axis,std::size_t index):
            source_(source),axis_(axis),index_(index){}
            std::size_t size() const{
                if(axis_==Axis::Row) return source_->colLength();
                if(axis_==Axis::Col) return source_->rowLength();
                return 0;
            }
            VType operator()(std::size_t i) const{
                EvalVisitor<VType> visitor;
                if(axis_==Axis::Row) return source_->accept(visitor,index_,i);
                if(axis_==Axis::Col) return source_->accept(visitor,i,index_);
                return {};
            }
        private:
            const Source *source_;
            Axis axis_;
            std::size_t index_;
    };
    */

    template<typename VType>
    class NodeVisitor{
        public:
            using size_type=std::size_t;

            virtual ~NodeVisitor()=default;
            
            virtual VType visit(const MatNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const NegLikeNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const AddLikeNode<VType> &node,size_type row,size_type col) const=0;
            virtual VType visit(const EwiseLikeNode<VType> &node,size_type row,size_type col) const=0;
    };

    template<typename VType>
    class EvalVisitor:public NodeVisitor<VType>{
        public:
            using size_type=std::size_t;
            
            VType visit(const MatNode<VType> &node,size_type row,size_type col) const override{
                return (*node.mat_)(row,col);
            }
            VType visit(const NegLikeNode<VType> &node,size_type row,size_type col) const override{
                VType val=node.node_->accept(*this,row,col);
                if(node.opr()==OprArithm::Neg){
                    if constexpr(opr_traits::isNegAble<VType>::value)
                        return arithmNeg(val);
                    else /*Operator Error*/;
                }else if(node.opr()==OprArithm::EwiseInv){
                    if constexpr(opr_traits::isDivAble<VType,VType>::value)
                        return arithmEwiseInv(val);
                    else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VType{};
            }
            VType visit(const AddLikeNode<VType> &node,size_type row,size_type col) const override{
                if(node.opr()==OprArithm::MatMul){
                    if constexpr(opr_traits::isMulAble<VType,VType>::value){
                        View<ASTNode<VType>> lhs(node.lhs_.get(),Axis::Row,row);
                        View<ASTNode<VType>> rhs(node.rhs_.get(),Axis::Col,col);
                        //ViewLike<ASTNode<VType>,VType> lhs(node.lhs_.get(),Axis::Row,row);
                        //ViewLike<ASTNode<VType>,VType> rhs(node.rhs_.get(),Axis::Col,col);
                        return arithmMatMul(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr()==OprArithm::Add){
                    if constexpr(opr_traits::isAddAble<VType,VType>::value){
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return arithmAdd(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr()==OprArithm::Sub){
                    if constexpr(opr_traits::isSubAble<VType,VType>::value){
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return arithmSub(lhs,rhs);
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
            return VType{};
            }
            VType visit(const EwiseLikeNode<VType> &node,size_type row,size_type col) const override{
                VType val=node.node_->accept(*this,row,col);
                VType arg=node.arg_;
                if(node.opr()==OprArithm::EwiseMul){
                    if constexpr(opr_traits::isMulAble<VType,VType>::value)
                        return arithmEwiseMul(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr()==OprArithm::EwiseDiv){
                    if constexpr(opr_traits::isDivAble<VType,VType>::value)
                        return arithmEwiseDiv(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr()==OprArithm::EwiseMod){
                    if constexpr(opr_traits::isModAble<VType,VType>::value)
                        return arithmEwiseMod(val,arg);
                    else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VType{};
            }
    };
}//namespace vtx