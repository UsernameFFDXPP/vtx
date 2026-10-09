#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType>::Expression(const Matrix<VType> *mat):
    root_(std::make_shared<MatNode<VType>>(OprDefault::Mat,mat)){}

    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr):
    root_(std::make_shared<NegLikeNode<VType>>(opr,expr.root_)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr):
    root_(std::make_shared<AddLikeNode<VType>>(opr,lexpr.root_,rexpr.root_)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,Axis axis):
    root_(std::make_shared<FlipLikeNode<VType>>(opr,expr.root_,axis)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr,Axis axis):
    root_(std::make_shared<ConcatLikeNode<VType>>(opr,lexpr.root_,rexpr.root_,axis)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,std::size_t idx1,std::size_t idx2):
    root_(std::make_shared<ResizeLikeNode<VType>>(opr,expr.root_,idx1,idx2)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,Axis axis,std::size_t idx):
    root_(std::make_shared<DropLikeNode<VType>>(opr,expr.root_,axis,idx)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,Axis axis,std::size_t idx1,std::size_t idx2):
    root_(std::make_shared<SwapLikeNode<VType>>(opr,expr.root_,axis,idx1,idx2)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,const VType &arg):
    root_(std::make_shared<EwiseLikeNode<VType>>(opr,expr.root_,arg)){}
    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,Axis axis,const VType &arg):
    root_(std::make_shared<QuantileLikeNode<VType>>(opr,expr.root_,arg)){}

    template<typename VType>
    std::size_t Expression<VType>::rowLength() const{
        return root_->rowLength();
    }
    template<typename VType>

    std::size_t Expression<VType>::colLength() const{
        return root_->colLength();
    }

    template<typename VType>
    Matrix<VType> Expression<VType>::eval() const{
        EvalVisitor<VType> visitor;
        std::size_t rows=root_->rowLength();
        std::size_t cols=root_->colLength();
        Matrix<VType> rsl(rows,cols);
        for(std::size_t row=0;row<rows;++row){
            for(std::size_t col=0;col<cols;++col){
                rsl(row,col)=root_->accept(visitor,row,col);
            }
        }
        return rsl;
    }

    template<typename VType>
    VType Expression<VType>::evalAt(std::size_t row,std::size_t col) const{
        EvalVisitor<VType> visitor;
        return root_->accept(visitor,row,col);
    }

    template<typename VType>
    VType Expression<VType>::operator()(std::size_t row,std::size_t col) const{
        return Expression<VType>::evalAt(row,col);
    }
}//namespace vtx