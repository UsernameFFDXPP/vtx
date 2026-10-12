#pragma once

#include<cstddef>
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
    template<typename VType> class FlipLikeNode;
    template<typename VType> class ConcatLikeNode;
    template<typename VType> class ResizeLikeNode;
    template<typename VType> class DropLikeNode;
    template<typename VType> class SwapLikeNode;
    template<typename VType> class EwiseLikeNode;
    template<typename VType> class QuantileLikeNode;
    
    template<typename VType,typename VTypeO> class NodeVisitor;
    template<typename VType,typename VTypeO> class EvalVisitor;

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

    template<typename VType,typename VTypeO>
    class NodeVisitor{
        public:
            using size_type=std::size_t;

            virtual ~NodeVisitor()=default;
            
            virtual VTypeO visit(const MatNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const NegLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const AddLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const FlipLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const ConcatLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const ResizeLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const DropLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const SwapLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const EwiseLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const QuantileLikeNode<VType> &node,std::size_t row,std::size_t col) const=0;
    };

    template<typename VType,typename VTypeO>
    class EvalVisitor:public NodeVisitor<VType,VTypeO>{
        public:
            using size_type=std::size_t;
            
            VTypeO visit(const MatNode<VType> &node,std::size_t row,std::size_t col) const override{
                return (*node.mat_)(row,col);
            }

            VTypeO visit(const NegLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprArithm::Neg){
                    if constexpr(opr_traits::getOprDemand<VType,OprArithm::Neg>()){
                        VType val=node.node_->accept(*this,row,col);
                        return algNeg(val);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseInv){
                    if constexpr(opr_traits::getOprDemand<VType,OprArithm::EwiseInv>()){
                        VType val=node.node_->accept(*this,row,col);
                        return algEwiseInv(val);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatInv){
                    if constexpr(opr_traits::getOprDemand<VType,OprArithm::MatInv>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Transpose){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Transpose>()){
                        return node.node_->accept(*this,col,row);
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const AddLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprArithm::Add){
                    if constexpr(opr_traits::isAddAble<VType,VType>::value){
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return algAdd(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::Sub){
                    if constexpr(opr_traits::isSubAble<VType,VType>::value){
                        VType lhs=node.lhs_->accept(*this,row,col);
                        VType rhs=node.rhs_->accept(*this,row,col);
                        return algSub(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatMul){
                    if constexpr(opr_traits::isMulAble<VType,VType>::value){
                        View<ASTNode<VType>> lhs(node.lhs_.get(),Axis::Row,row);
                        View<ASTNode<VType>> rhs(node.rhs_.get(),Axis::Col,col);
                        //ViewLike<ASTNode<VType>,VType> lhs(node.lhs_.get(),Axis::Row,row);
                        //ViewLike<ASTNode<VType>,VType> rhs(node.rhs_.get(),Axis::Col,col);
                        return algMatMul(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatDiv){
                    if constexpr(opr_traits::getOprDemand<VType,OprArithm::MatDiv>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Equal){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::Equal>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Greater){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::Greater>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::GreaterEqual){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::GreaterEqual>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Less){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::Less>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::LessEqual){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::LessEqual>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::NotEqual){
                    if constexpr(opr_traits::getOprDemand<VType,OprCompare::NotEqual>()){

                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const FlipLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Flip){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Flip>()){
                        if(node.axis_==Axis::Row){
                            return node.node_->accept(*this,node.rowLength_-1-row,col);
                        }else if(node.axis_==Axis::Col){
                            return node.node_->accept(*this,row,node.colLength_-1-col);
                        }else if(node.axis_==Axis::None){
                            return node.node_->accept(*this,node.rowLength_-1-row,node.colLength_-1-col);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Sum){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Sum>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Max){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Max>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Min){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::Min>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::ArgMax){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMax>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::ArgMin){
                    if constexpr(opr_traits::getOprDemand<VType,OprReduction::ArgMin>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Covariance){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Covariance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Correlation){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Correlation>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Mean){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Mean>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Variance){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Variance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::SampleVariance){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::SampleVariance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Median){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Median>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Center){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Center>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Standardize){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Standardize>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::SampleStandardize){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::SampleStandardize>()){

                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const ConcatLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Concat){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Concat>()){
                        if(node.axis_==Axis::Row){
                            std::size_t rows=node.lhs_->rowLength_;
                            if(row<rows) return node.lhs_->accept(*this,row,col);
                            else return node.rhs_->accept(*this,row-rows,col);
                        }else if(node.axis_==Axis::Col){
                            std::size_t cols=node.lhs_->colLength_;
                            if(col<cols) return node.lhs_->accept(*this,row,col);
                            else return node.rhs_->accept(*this,row,col-cols);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const ResizeLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Reshape){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Reshape>()){
                        std::size_t idx=row*(node.idx2_)+col;
                        std::size_t rowP=idx/(node.node_->colLength_);
                        std::size_t colP=idx%(node.node_->colLength_);
                        return node.node_->accept(*this,rowP,colP);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Resize){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Resize>()){
                        if(row<node.idx1_ && col<node.idx2_){
                            return node.node_->accept(*this,row,col);
                        }else return VTypeO{};
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const DropLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Drop){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Drop>()){
                        if(node.axis_==Axis::Row){
                            if(row<node.idx_) return node.node_->accept(*this,row,col);
                            else return node.node_->accept(*this,row+1,col);
                        }else if(node.axis_==Axis::Col){
                            if(col<node.idx_) return node.node_->accept(*this,row,col);
                            else return node.node_->accept(*this,row,col+1);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Insert){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Insert>()){
                        if(node.axis_==Axis::Row){
                            if(row<node.idx_) return node.node_->accept(*this,row,col);
                            else if(row==node.idx_) return VTypeO{};
                            else return node.node_->accept(*this,row-1,col);
                        }else if(node.axis_==Axis::Col){
                            if(col<node.idx_) return node.node_->accept(*this,row,col);
                            else if(col==node.idx_) return VTypeO{};
                            else return node.node_->accept(*this,row,col-1);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const SwapLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Swap){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Swap>()){
                        if(node.axis_==Axis::Row){
                            if(row==node.idx1_) return node.node_->accept(*this,node.idx2_,col);
                            else if(row==node.idx2_) return node.node_->accept(*this,node.idx1_,col);
                            else return node.node_->accept(*this,row,col);
                        }else if(node.axis_==Axis::Col){
                            if(col==node.idx1_) return node.node_->accept(*this,row,node.idx2_);
                            else if(col==node.idx2_) return node.node_->accept(*this,row,node.idx1_);
                            else return node.node_->accept(*this,row,col);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Slice){
                    if constexpr(opr_traits::getOprDemand<VType,OprLayout::Slice>()){
                        if(node.axis_==Axis::Row){
                            return node.node_->accept(*this,row-node.idx1_,col);
                        }else if(node.axis_==Axis::Col){
                            return node.node_->accept(*this,row,col-node.idx1_);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const EwiseLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                VType val=node.node_->accept(*this,row,col);
                VType arg=node.arg_;
                if(node.opr_==OprArithm::EwiseMul){
                    if constexpr(opr_traits::isMulAble<VType,VType>::value)
                        return algEwiseMul(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseDiv){
                    if constexpr(opr_traits::isDivAble<VType,VType>::value)
                        return algEwiseDiv(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseMod){
                    if constexpr(opr_traits::isModAble<VType,VType>::value)
                        return algEwiseMod(val,arg);
                    else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const QuantileLikeNode<VType> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VType,OprStatistics::Quantile>()){

                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }
    };
}//namespace vtx