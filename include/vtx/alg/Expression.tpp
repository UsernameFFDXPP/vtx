#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType>::Expression(const Matrix<VType> *mat):
    root_(std::make_shared<MatNode<VType,VType>>(OprDefault::Mat,mat)){}

    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr):
    root_(std::make_shared<NegLikeNode<VTypeI,VTypeO>>(opr,expr.root_)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &lexpr,const Expression<VTypeI> &rexpr):
    root_(std::make_shared<AddLikeNode<VTypeI,VTypeO>>(opr,lexpr.root_,rexpr.root_)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis):
    root_(std::make_shared<FlipLikeNode<VTypeI,VTypeO>>(opr,expr.root_,axis)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &lexpr,const Expression<VTypeI> &rexpr,Axis axis):
    root_(std::make_shared<ConcatLikeNode<VTypeI,VTypeO>>(opr,lexpr.root_,rexpr.root_,axis)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,std::size_t idx1,std::size_t idx2):
    root_(std::make_shared<ResizeLikeNode<VTypeI,VTypeO>>(opr,expr.root_,idx1,idx2)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,std::size_t idx):
    root_(std::make_shared<DropLikeNode<VTypeI,VTypeO>>(opr,expr.root_,axis,idx)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,std::size_t idx1,std::size_t idx2):
    root_(std::make_shared<SwapLikeNode<VTypeI,VTypeO>>(opr,expr.root_,axis,idx1,idx2)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,const VTypeI &arg):
    root_(std::make_shared<EwiseLikeNode<VTypeI,VTypeO>>(opr,expr.root_,arg)){}
    template<typename VTypeO>
    template<typename VTypeI>
    Expression<VTypeO>::Expression(Operator opr,const Expression<VTypeI> &expr,Axis axis,double arg):
    root_(std::make_shared<QuantileLikeNode<VTypeI,VTypeO>>(opr,expr.root_,arg)){}

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
        std::size_t rows=root_->rowLength();
        std::size_t cols=root_->colLength();
        Matrix<VType> rsl(rows,cols);
        for(std::size_t row=0;row<rows;++row){
            for(std::size_t col=0;col<cols;++col){
                rsl(row,col)=root_->evalAt(row,col);
            }
        }
        return rsl;
    }

    template<typename VType>
    VType Expression<VType>::evalAt(std::size_t row,std::size_t col) const{
        return root_->evalAt(row,col);
    }

    template<typename VType>
    VType Expression<VType>::operator()(std::size_t row,std::size_t col) const{
        return Expression<VType>::evalAt(row,col);
    }
}//namespace vtx