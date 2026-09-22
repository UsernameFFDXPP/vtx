#include<cstddef>

#include"vtx/alg/ASTNode.hpp"

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

    template<typename VType>
    Operation ASTNode<VType>::opr() const{
        return opr_;
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
    VType MatNode<VType>::accept(const NodeVisitor<VType> &visitor,typename MatNode<VType>::size_type row,typename MatNode<VType>::size_type col) const{
        return visitor.visit(*this,row,col);
    }

    /*Unary*/
    template<typename VType>
    UnaryNode<VType>::UnaryNode(Operation opr,typename UnaryNode<VType>::node_sptr node):
    node_(node){
        this->opr_=opr;
        if(opr==Operation::Neg){
            this->rowLength_=node->rowLength();
            this->colLength_=node->colLength();
        }else if(opr==Operation::MatInv){
            this->rowLength_=node->colLength();
            this->colLength_=node->rowLength();
        }else if(opr==Operation::Transpose){
            this->rowLength_=node->colLength();
            this->colLength_=node->rowLength();
        }else{
            /*Operation Error*/
        }
    }
    
    template<typename VType>
    VType UnaryNode<VType>::accept(const NodeVisitor<VType> &visitor,typename UnaryNode<VType>::size_type row,typename UnaryNode<VType>::size_type col) const{
        return visitor.visit(*this,row,col);
    }

    /*Binary*/
    template<typename VType>
    BinaryNode<VType>::BinaryNode(Operation opr,typename BinaryNode<VType>::node_sptr lhs,typename BinaryNode<VType>::node_sptr rhs):
    lhs_(lhs),rhs_(rhs){
        this->opr_=opr;
        if(opr==Operation::Add || opr==Operation::Sub){
            this->rowLength_=lhs->rowLength();
            this->colLength_=lhs->colLength();
        }else if(opr==Operation::MatMul){
            this->rowLength_=lhs->rowLength();
            this->colLength_=rhs->colLength();
        }else{
            /*Operation Error*/
        }
    }
    
    template<typename VType>
    VType BinaryNode<VType>::accept(const NodeVisitor<VType> &visitor,typename BinaryNode<VType>::size_type row,typename BinaryNode<VType>::size_type col) const{
        return visitor.visit(*this,row,col);
    }
    
    /*Arg*/
    template<typename VType>
    ArgNode<VType>::ArgNode(Operation opr,typename ArgNode<VType>::node_sptr node,VType arg):
    node_(node),arg_(arg){
        this->opr_=opr;
        this->rowLength_=node->rowLength();
        this->colLength_=node->colLength();
    }
    
    template<typename VType>
    VType ArgNode<VType>::accept(const NodeVisitor<VType> &visitor,typename ArgNode<VType>::size_type row,typename ArgNode<VType>::size_type col) const{
        return visitor.visit(*this,row,col);
    }
}//namespace vtx
