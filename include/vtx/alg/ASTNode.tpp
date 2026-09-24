#include<cstddef>

#include"vtx/alg/ASTNode.hpp"

namespace vtx{
    template<typename VType>
    ASTNode<VType>::ASTNode():
    rowLength_(0),colLength_(0),opr_(OprDefault::None){}

    template<typename VType>
    std::size_t ASTNode<VType>::rowLength() const{
        return rowLength_;
    }
    template<typename VType>
    std::size_t ASTNode<VType>::colLength() const{
        return colLength_;
    }
    template<typename VType>
    Operator ASTNode<VType>::opr() const{
        return opr_;
    }

    template<typename VType>
    VType ASTNode<VType>::operator()(std::size_t row,std::size_t col) const{
        EvalVisitor<VType> visitor;
        return accept(visitor,row,col);
    }

    /*Mat*/
    template<typename VType>
    MatNode<VType>::MatNode(Operator opr,const Matrix<VType> *mat):
    mat_(mat){
        this->opr_=opr;
        this->rowLength_=mat->rowLength();
        this->colLength_=mat->colLength();
    }
    template<typename VType>
    VType MatNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*NegLike*/
    template<typename VType>
    NegLikeNode<VType>::NegLikeNode(Operator opr,typename NegLikeNode<VType>::node_sptr node):
    node_(node){
        this->opr_=opr;
        if(opr==OprArithm::Neg){
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
    template<typename VType>
    VType NegLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*AddLike*/
    template<typename VType>
    AddLikeNode<VType>::AddLikeNode(Operator opr,typename AddLikeNode<VType>::node_sptr lhs,typename AddLikeNode<VType>::node_sptr rhs):
    lhs_(lhs),rhs_(rhs){
        this->opr_=opr;
        if(opr==OprArithm::Add || opr==OprArithm::Sub){
            this->rowLength_=lhs->rowLength();
            this->colLength_=lhs->colLength();
        }else if(opr==OprArithm::MatMul){
            this->rowLength_=lhs->rowLength();
            this->colLength_=rhs->colLength();
        }else{
            /*Operator Error*/
        }
    }
    template<typename VType>
    VType AddLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*FlipLike*/
    template<typename VType>
    FlipLikeNode<VType>::FlipLikeNode(Operator opr,typename FlipLikeNode<VType>::node_sptr node,Axis axis):
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
    template<typename VType>
    VType FlipLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*ConcatLike*/
    template<typename VType>
    ConcatLikeNode<VType>::ConcatLikeNode(Operator opr,typename ConcatLikeNode<VType>::node_sptr lhs,typename ConcatLikeNode<VType>::node_sptr rhs,Axis axis):
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
    template<typename VType>
    VType ConcatLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*ResizeLike*/
    template<typename VType>
    ResizeLikeNode<VType>::ResizeLikeNode(Operator opr,typename ResizeLikeNode<VType>::node_sptr node,std::size_t idx1,std::size_t idx2):
    node_(node),idx1_(idx1),idx2_(idx2){
        this->opr_=opr;
        if(opr==OprLayout::Reshape || opr==OprLayout::Resize){
            this->rowLength_=idx1;
            this->colLength_=idx2;
        }else{
            /*Operator Error*/
        }
    }
    template<typename VType>
    VType ResizeLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*DropLike*/
    template<typename VType>
    DropLikeNode<VType>::DropLikeNode(Operator opr,typename DropLikeNode<VType>::node_sptr node,Axis axis,std::size_t idx):
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
    template<typename VType>
    VType DropLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*SwapLike*/
    template<typename VType>
    SwapLikeNode<VType>::SwapLikeNode(Operator opr,typename SwapLikeNode<VType>::node_sptr node,Axis axis,std::size_t idx1,std::size_t idx2):
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
    template<typename VType>
    VType SwapLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
    
    /*EwiseLike*/
    template<typename VType>
    EwiseLikeNode<VType>::EwiseLikeNode(Operator opr,typename EwiseLikeNode<VType>::node_sptr node,VType arg):
    node_(node),arg_(arg){
        this->opr_=opr;
        this->rowLength_=node->rowLength();
        this->colLength_=node->colLength();
    }
    
    template<typename VType>
    VType EwiseLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*QuantileLike*/
    template<typename VType>
    QuantileLikeNode<VType>::QuantileLikeNode(Operator opr,typename QuantileLikeNode<VType>::node_sptr node,Axis axis,VType arg):
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
    template<typename VType>
    VType QuantileLikeNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
}//namespace vtx
