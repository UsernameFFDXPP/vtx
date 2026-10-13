#pragma once

#include<cstddef>
#include<cstddef>

#include"vtx/core/Axis.hpp"

#include"vtx/core/View.hpp"
#include"vtx/alg/Operator.hpp"
#include"vtx/alg/arithm/Arithm.hpp"
#include"vtx/alg/compare/Compare.hpp"

namespace vtx{
    template<typename VType> class NodeBase;

    template<typename VTypeI,typename VTypeO> class ASTNode;
    template<typename VTypeI,typename VTypeO> class MatNode;
    template<typename VTypeI,typename VTypeO> class NegLikeNode;
    template<typename VTypeI,typename VTypeO> class AddLikeNode;
    template<typename VTypeI,typename VTypeO> class FlipLikeNode;
    template<typename VTypeI,typename VTypeO> class ConcatLikeNode;
    template<typename VTypeI,typename VTypeO> class ResizeLikeNode;
    template<typename VTypeI,typename VTypeO> class DropLikeNode;
    template<typename VTypeI,typename VTypeO> class SwapLikeNode;
    template<typename VTypeI,typename VTypeO> class EwiseLikeNode;
    template<typename VTypeI,typename VTypeO> class QuantileLikeNode;
    
    template<typename VTypeI,typename VTypeO> class NodeVisitor;
    template<typename VTypeI,typename VTypeO> class EvalVisitor;

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

    template<typename VTypeI,typename VTypeO>
    class NodeVisitor{
        public:
            using size_type=std::size_t;

            virtual ~NodeVisitor()=default;
            
            virtual VTypeO visit(const MatNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const NegLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const AddLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const FlipLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const ConcatLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const ResizeLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const DropLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const SwapLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const EwiseLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
            virtual VTypeO visit(const QuantileLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const=0;
    };

    template<typename VTypeI,typename VTypeO>
    class EvalVisitor:public NodeVisitor<VTypeI,VTypeO>{
        public:
            using size_type=std::size_t;
            
            VTypeO visit(const MatNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                return (*node.mat_)(row,col);
            }

            VTypeO visit(const NegLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprArithm::Neg){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::Neg>()){
                        VTypeI val=node.node_->evalAt(row,col);
                        return algNeg(val);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseInv){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::EwiseInv>()){
                        VTypeI val=node.node_->evalAt(row,col);
                        return algEwiseInv(val);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatInv){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::MatInv>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Transpose){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Transpose>()){
                        return node.node_->evalAt(col,row);
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const AddLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprArithm::Add){
                    if constexpr(opr_traits::isAddAble<VTypeI,VTypeI>::value){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algAdd(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::Sub){
                    if constexpr(opr_traits::isSubAble<VTypeI,VTypeI>::value){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algSub(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatMul){
                    if constexpr(opr_traits::isMulAble<VTypeI,VTypeI>::value){
                        View<NodeBase<VTypeI>> lhs(node.lhs_.get(),Axis::Row,row);
                        View<NodeBase<VTypeI>> rhs(node.rhs_.get(),Axis::Col,col);
                        //ViewLike<ASTNode<VType>,VType> lhs(node.lhs_.get(),Axis::Row,row);
                        //ViewLike<ASTNode<VType>,VType> rhs(node.rhs_.get(),Axis::Col,col);
                        return algMatMul(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprArithm::MatDiv){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprArithm::MatDiv>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Equal){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Equal>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algEqual(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Greater){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Greater>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algGreater(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::GreaterEqual){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::GreaterEqual>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algGreaterEqual(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::Less){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::Less>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algLess(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::LessEqual){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::LessEqual>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algLessEqual(lhs,rhs);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprCompare::NotEqual){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprCompare::NotEqual>()){
                        VTypeI lhs=node.lhs_->evalAt(row,col);
                        VTypeI rhs=node.rhs_->evalAt(row,col);
                        return algNotEqual(lhs,rhs);
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const FlipLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Flip){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Flip>()){
                        if(node.axis_==Axis::Row){
                            return node.node_->evalAt(node.rowLength_-1-row,col);
                        }else if(node.axis_==Axis::Col){
                            return node.node_->evalAt(row,node.colLength_-1-col);
                        }else if(node.axis_==Axis::None){
                            return node.node_->evalAt(node.rowLength_-1-row,node.colLength_-1-col);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Sum){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Sum>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Max){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Max>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::Min){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::Min>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::ArgMax){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMax>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprReduction::ArgMin){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprReduction::ArgMin>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Covariance){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Covariance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Correlation){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Correlation>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Mean){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Mean>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Variance){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Variance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::SampleVariance){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::SampleVariance>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Median){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Median>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Center){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Center>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::Standardize){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Standardize>()){

                    }else /*Operator Error*/;
                }else if(node.opr_==OprStatistics::SampleStandardize){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::SampleStandardize>()){

                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const ConcatLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Concat){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Concat>()){
                        if(node.axis_==Axis::Row){
                            std::size_t rows=node.lhs_->rowLength();
                            if(row<rows) return node.lhs_->evalAt(row,col);
                            else return node.rhs_->evalAt(row-rows,col);
                        }else if(node.axis_==Axis::Col){
                            std::size_t cols=node.lhs_->colLength();
                            if(col<cols) return node.lhs_->evalAt(row,col);
                            else return node.rhs_->evalAt(row,col-cols);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const ResizeLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Reshape){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Reshape>()){
                        std::size_t idx=row*(node.idx2_)+col;
                        std::size_t rowP=idx/(node.node_->colLength());
                        std::size_t colP=idx%(node.node_->colLength());
                        return node.node_->evalAt(rowP,colP);
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Resize){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Resize>()){
                        if(row<node.idx1_ && col<node.idx2_){
                            return node.node_->evalAt(row,col);
                        }else return VTypeO{};
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const DropLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Drop){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Drop>()){
                        if(node.axis_==Axis::Row){
                            if(row<node.idx_) return node.node_->evalAt(row,col);
                            else return node.node_->evalAt(row+1,col);
                        }else if(node.axis_==Axis::Col){
                            if(col<node.idx_) return node.node_->evalAt(row,col);
                            else return node.node_->evalAt(row,col+1);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Insert){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Insert>()){
                        if(node.axis_==Axis::Row){
                            if(row<node.idx_) return node.node_->evalAt(row,col);
                            else if(row==node.idx_) return VTypeO{};
                            else return node.node_->evalAt(row-1,col);
                        }else if(node.axis_==Axis::Col){
                            if(col<node.idx_) return node.node_->evalAt(row,col);
                            else if(col==node.idx_) return VTypeO{};
                            else return node.node_->evalAt(row,col-1);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const SwapLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprLayout::Swap){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Swap>()){
                        if(node.axis_==Axis::Row){
                            if(row==node.idx1_) return node.node_->evalAt(node.idx2_,col);
                            else if(row==node.idx2_) return node.node_->evalAt(node.idx1_,col);
                            else return node.node_->evalAt(row,col);
                        }else if(node.axis_==Axis::Col){
                            if(col==node.idx1_) return node.node_->evalAt(row,node.idx2_);
                            else if(col==node.idx2_) return node.node_->evalAt(row,node.idx1_);
                            else return node.node_->evalAt(row,col);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else if(node.opr_==OprLayout::Slice){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprLayout::Slice>()){
                        if(node.axis_==Axis::Row){
                            return node.node_->evalAt(row-node.idx1_,col);
                        }else if(node.axis_==Axis::Col){
                            return node.node_->evalAt(row,col-node.idx1_);
                        }else /*Axis Error*/;
                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const EwiseLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                VTypeI val=node.node_->evalAt(row,col);
                VTypeI arg=node.arg_;
                if(node.opr_==OprArithm::EwiseMul){
                    if constexpr(opr_traits::isMulAble<VTypeI,VTypeI>::value)
                        return algEwiseMul(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseDiv){
                    if constexpr(opr_traits::isDivAble<VTypeI,VTypeI>::value)
                        return algEwiseDiv(val,arg);
                    else /*Operator Error*/;
                }else if(node.opr_==OprArithm::EwiseMod){
                    if constexpr(opr_traits::isModAble<VTypeI,VTypeI>::value)
                        return algEwiseMod(val,arg);
                    else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }

            VTypeO visit(const QuantileLikeNode<VTypeI,VTypeO> &node,std::size_t row,std::size_t col) const override{
                if(node.opr_==OprStatistics::Quantile){
                    if constexpr(opr_traits::getOprDemand<VTypeI,OprStatistics::Quantile>()){

                    }else /*Operator Error*/;
                }else{
                    /*Operator Error*/;
                }
                return VTypeO{};
            }
    };
}//namespace vtx