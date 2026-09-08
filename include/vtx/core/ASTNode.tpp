#include<cstddef>

#include"vtx/core/ASTNode.hpp"
#include"vtx/alg/Arithm.hpp"

namespace vtx{
    template<typename VType>
    ASTNode<VType>::ASTNode():
        rowLength_(0),colLength_(0),opr_(Operation::None){}

    template<typename VType>
    typename ASTNode<VType>::size_type ASTNode<VType>::rowLength() const{
        return rowLength_;
    }

    template<typename VType>
    typename ASTNode<VType>::size_type ASTNode<VType>::colLength() const{
        return colLength_;
    }

    /*Mat*/
    template<typename VType>
    MatNode<VType>::MatNode(Operation opr,const Matrix<VType> *mat):
        mat_(mat){
            this->opr_=opr;
            this->rowLength_=mat->rowLength();
            this->colLength_=mat->colLength();
        }

    template<typename VType>
    VType MatNode<VType>::evalAt(typename MatNode<VType>::size_type row,typename MatNode<VType>::size_type col) const{
        return (*mat_)(row,col);
    }

    /*Unary*/
    template<typename VType>
    UnaryNode<VType>::UnaryNode(Operation opr,typename UnaryNode<VType>::node_sptr node):
        node_(node){
            this->opr_=opr;
            if(opr==Operation::Neg){
                this->rowLength_=node->rowLength();
                this->colLength_=node->colLength();
            }else if(opr==Operation::Transpose){
                this->rowLength_=node->colLength();
                this->colLength_=node->rowLength();
            }else if(opr==Operation::MatInv){

            }
            
        }

    template<typename VType>
    VType UnaryNode<VType>::evalAt(size_type row,size_type col) const{
        return unaryEwiseArithm(this->opr_,node_->evalAt(row,col));
    }

    /*Binary*/
    template<typename VType>
    BinaryNode<VType>::BinaryNode(Operation opr,typename BinaryNode<VType>::node_sptr lhs,typename BinaryNode<VType>::node_sptr rhs):
        lhs_(lhs),rhs_(rhs){
            this->opr_=opr;
            if(opr==Operation::MatMul){
                this->rowLength_=lhs->rowLength();
                this->colLength_=rhs->colLength();
            }else{
                this->rowLength_=lhs->rowLength();
                this->colLength_=lhs->colLength();
            }
            
        }

    template<typename VType>
    VType BinaryNode<VType>::evalAt(std::size_t row,std::size_t col) const{
        return binaryEwiseArithm(this->opr_,lhs_->evalAt(row,col),rhs_->evalAt(row,col));
    }
}
