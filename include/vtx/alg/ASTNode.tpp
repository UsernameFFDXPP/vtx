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

    /*Unary*/
    template<typename VType>
    UnaryNode<VType>::UnaryNode(Operator opr,typename UnaryNode<VType>::node_sptr node):
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
    VType UnaryNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }

    /*Binary*/
    template<typename VType>
    BinaryNode<VType>::BinaryNode(Operator opr,typename BinaryNode<VType>::node_sptr lhs,typename BinaryNode<VType>::node_sptr rhs):
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
    VType BinaryNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
    
    /*Arg*/
    template<typename VType>
    ArgNode<VType>::ArgNode(Operator opr,typename ArgNode<VType>::node_sptr node,VType arg):
    node_(node),arg_(arg){
        this->opr_=opr;
        this->rowLength_=node->rowLength();
        this->colLength_=node->colLength();
    }
    
    template<typename VType>
    VType ArgNode<VType>::accept(const NodeVisitor<VType> &visitor,std::size_t row,std::size_t col) const{
        return visitor.visit(*this,row,col);
    }
}//namespace vtx
