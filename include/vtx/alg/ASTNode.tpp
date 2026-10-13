#include<cstddef>

#include"vtx/alg/ASTNode.hpp"

namespace vtx{
    template<typename VTypeI,typename VTypeO>
    ASTNode<VTypeI,VTypeO>::ASTNode():
    rowLength_(0),colLength_(0),opr_(OprDefault::None){}

    template<typename VTypeI,typename VTypeO>
    std::size_t ASTNode<VTypeI,VTypeO>::rowLength() const{
        return rowLength_;
    }
    template<typename VTypeI,typename VTypeO>
    std::size_t ASTNode<VTypeI,VTypeO>::colLength() const{
        return colLength_;
    }
    template<typename VTypeI,typename VTypeO>
    Operator ASTNode<VTypeI,VTypeO>::opr() const{
        return opr_;
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO ASTNode<VTypeI,VTypeO>::evalAt(std::size_t row,std::size_t col) const{
        EvalVisitor<VTypeI,VTypeO> visitor;
        return accept(visitor,row,col);
    }

    template<typename VTypeI,typename VTypeO>
    VTypeO ASTNode<VTypeI,VTypeO>::operator()(std::size_t row,std::size_t col) const{
        EvalVisitor<VTypeI,VTypeO> visitor;
        return accept(visitor,row,col);
    }

    /*Mat*/
    template<typename VTypeI,typename VTypeO>
    MatNode<VTypeI,VTypeO>::MatNode(Operator opr,const Matrix<VTypeI> *mat):
    mat_(mat){
        this->opr_=opr;
        this->rowLength_=mat->rowLength();
        this->colLength_=mat->colLength();
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO MatNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*NegLike*/
    template<typename VTypeI,typename VTypeO>
    NegLikeNode<VTypeI,VTypeO>::NegLikeNode(Operator opr,typename NegLikeNode<VTypeI,VTypeO>::node_sptr node):
    node_(node){
        this->opr_=opr;
        if(opr==OprArithm::Neg){
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else if(opr==OprArithm::EwiseInv){
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else if(opr==OprArithm::MatInv){
            this->rowLength_=node->colLength();
            this->colLength_=node->rowLength();
        }else if(opr==OprLayout::Transpose){
            this->rowLength_=node->colLength();
            this->colLength_=node->rowLength();
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO NegLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*AddLike*/
    template<typename VTypeI,typename VTypeO>
    AddLikeNode<VTypeI,VTypeO>::AddLikeNode(Operator opr,typename AddLikeNode<VTypeI,VTypeO>::node_sptr lhs,typename AddLikeNode<VTypeI,VTypeO>::node_sptr rhs):
    lhs_(lhs),rhs_(rhs){
        this->opr_=opr;
        if(
            opr==OprArithm::Add || opr==OprArithm::Sub ||
            opr==OprCompare::Equal || opr==OprCompare::NotEqual ||
            opr==OprCompare::Greater || opr==OprCompare::LessEqual ||
            opr==OprCompare::Less || opr==OprCompare::GreaterEqual
        ){
            this->rowLength_=lhs->rowLength();
            this->colLength_=lhs->colLength();
        }else if(opr==OprArithm::MatMul){
            this->rowLength_=lhs->rowLength();
            this->colLength_=rhs->colLength();
        }else if(opr==OprArithm::MatDiv){
            //this->rowLength_=lhs->rowLength();
            //this->colLength_=lhs->colLength();
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO AddLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*FlipLike*/
    template<typename VTypeI,typename VTypeO>
    FlipLikeNode<VTypeI,VTypeO>::FlipLikeNode(Operator opr,typename FlipLikeNode<VTypeI,VTypeO>::node_sptr node,Axis axis):
    node_(node),axis_(axis){
        this->opr_=opr;
        if(opr==OprLayout::Flip){
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else if(
            opr==OprReduction::Sum ||
            opr==OprReduction::Max ||
            opr==OprReduction::Min ||
            opr==OprReduction::ArgMax ||
            opr==OprReduction::ArgMin ||
            opr==OprStatistics::Mean ||
            opr==OprStatistics::Variance ||
            opr==OprStatistics::SampleVariance ||
            opr==OprStatistics::Median
        ){  
            if(axis==Axis::Row){
                this->rowLength_=node->rowLength();
                this->colLength_=1;
            }else if(axis==Axis::Col){
                this->rowLength_=1;
                this->colLength_=node->colLength();
            }else if(axis==Axis::None){
                this->rowLength_=1;
                this->colLength_=1;
            }else;
        }else if(
            opr==OprStatistics::Center ||
            opr==OprStatistics::Standardize
        ){  
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO FlipLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*ConcatLike*/
    template<typename VTypeI,typename VTypeO>
    ConcatLikeNode<VTypeI,VTypeO>::ConcatLikeNode(Operator opr,typename ConcatLikeNode<VTypeI,VTypeO>::node_sptr lhs,typename ConcatLikeNode<VTypeI,VTypeO>::node_sptr rhs,Axis axis):
    lhs_(lhs),rhs_(rhs),axis_(axis){
        this->opr_=opr;
        if(opr==OprLayout::Concat){
            if(axis==Axis::Row){
                this->rowLength_=lhs->rowLength()+rhs->rowLength();
                this->colLength_=lhs->colLength();
            }else if(axis==Axis::Col){
                this->rowLength_=lhs->rowLength();
                this->colLength_=lhs->colLength()+rhs->colLength();
            }else if(axis==Axis::None){
                /*Axis Error*/
            }else;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO ConcatLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*ResizeLike*/
    template<typename VTypeI,typename VTypeO>
    ResizeLikeNode<VTypeI,VTypeO>::ResizeLikeNode(Operator opr,typename ResizeLikeNode<VTypeI,VTypeO>::node_sptr node,std::size_t idx1,std::size_t idx2):
    node_(node),idx1_(idx1),idx2_(idx2){
        this->opr_=opr;
        if(opr==OprLayout::Reshape || opr==OprLayout::Resize){
            this->rowLength_=idx1;
            this->colLength_=idx2;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO ResizeLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*DropLike*/
    template<typename VTypeI,typename VTypeO>
    DropLikeNode<VTypeI,VTypeO>::DropLikeNode(Operator opr,typename DropLikeNode<VTypeI,VTypeO>::node_sptr node,Axis axis,std::size_t idx):
    node_(node),axis_(axis),idx_(idx){
        this->opr_=opr;
        if(opr==OprLayout::Insert){
            if(axis==Axis::Row){
                this->rowLength_=node->rowLength()+1;
                this->colLength_=node->colLength();
            }else if(axis==Axis::Col){
                this->rowLength_=node->rowLength();
                this->colLength_=node->colLength()+1;
            }else if(axis==Axis::None){
                /*Axis Error*/
            }else;
        }else if(opr==OprLayout::Drop){
            if(axis==Axis::Row){
                this->rowLength_=node->rowLength()-1;
                this->colLength_=node->colLength();
            }else if(axis==Axis::Col){
                this->rowLength_=node->rowLength();
                this->colLength_=node->colLength()-1;
            }else if(axis==Axis::None){
                /*Axis Error*/
            }else;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO DropLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*SwapLike*/
    template<typename VTypeI,typename VTypeO>
    SwapLikeNode<VTypeI,VTypeO>::SwapLikeNode(Operator opr,typename SwapLikeNode<VTypeI,VTypeO>::node_sptr node,Axis axis,std::size_t idx1,std::size_t idx2):
    node_(node),axis_(axis),idx1_(idx1),idx2_(idx2){
        this->opr_=opr;
        if(opr==OprLayout::Swap){
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else if(opr==OprLayout::Slice){
            if(axis==Axis::Row){
                this->rowLength_=idx2-idx1;
                this->colLength_=node->colLength();
            }else if(axis==Axis::Col){
                this->rowLength_=node->rowLength();
                this->colLength_=idx2-idx1;
            }else if(axis==Axis::None){
                /*Axis Error*/
            }else;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO SwapLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
    
    /*EwiseLike*/
    template<typename VTypeI,typename VTypeO>
    EwiseLikeNode<VTypeI,VTypeO>::EwiseLikeNode(Operator opr,typename EwiseLikeNode<VTypeI,VTypeO>::node_sptr node,VTypeI arg):
    node_(node),arg_(arg){
        this->opr_=opr;
        this->rowLength_=node->rowLength();
        this->colLength_=node->colLength();
    }
    
    template<typename VTypeI,typename VTypeO>
    VTypeO EwiseLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*QuantileLike*/
    template<typename VTypeI,typename VTypeO>
    QuantileLikeNode<VTypeI,VTypeO>::QuantileLikeNode(Operator opr,typename QuantileLikeNode<VTypeI,VTypeO>::node_sptr node,Axis axis,VTypeI arg):
    node_(node),axis_(axis),arg_(arg){
        this->opr_=opr;
        if(opr==OprStatistics::Quantile){
            if(axis==Axis::Row){
                this->rowLength_=node->rowLength();
                this->colLength_=1;
            }else if(axis==Axis::Col){
                this->rowLength_=1;
                this->colLength_=node->colLength();
            }else if(axis==Axis::None){
                this->rowLength_=1;
                this->colLength_=1;
            }else;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VTypeI,typename VTypeO>
    VTypeO QuantileLikeNode<VTypeI,VTypeO>::accept(const NodeVisitor<VTypeI,VTypeO> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
}//namespace vtx
