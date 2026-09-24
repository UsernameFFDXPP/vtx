#include"vtx/alg/Expression.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType>::Expression(const Matrix<VType> *mat):
    root_(std::make_shared<MatNode<value_type>>(OprDefault::Mat,mat)){}

    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr):
    root_(std::make_shared<NegLikeNode<value_type>>(opr,expr.root_)){}

    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr):
    root_(std::make_shared<AddLikeNode<value_type>>(opr,lexpr.root_,rexpr.root_)){}

    template<typename VType>
    Expression<VType>::Expression(Operator opr,const Expression<VType> &expr,const VType &arg):
    root_(std::make_shared<EwiseLikeNode<value_type>>(opr,expr.root_,arg)){}

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
        size_type rows=root_->rowLength();
        size_type cols=root_->colLength();
        Matrix<VType> rsl(rows,cols);
        for(size_type row=0;row<rows;++row){
            for(size_type col=0;col<cols;++col){
                rsl(row,col)=root_->accept(visitor,row,col);
            }
        }
        return rsl;
    }

    template<typename VType>
    VType Expression<VType>::evalAt(size_type row,size_type col) const{
        EvalVisitor<VType> visitor;
        if(useTempRsl_ && tempRslMask_(row,col)) return tempRsl_(row,col);
        VType rsl=root_->accept(visitor,row,col);
        if(useTempRsl_){
            /*
            tempRsl_(row,col)=rsl;
            tempRslMask_(row,col)=true;
            */
        }
        return rsl;
    }

    template<typename VType>
    VType Expression<VType>::operator()(size_type row,size_type col) const{
        return Expression<VType>::evalAt(row,col);
    }

    template<typename VType>
    bool Expression<VType>::useTempRsl() const{
        return useTempRsl_;
    }

    template<typename VType>
    void Expression<VType>::setTempRsl(bool set){
        useTempRsl_=set;
        return;
    }
}//namespace vtx