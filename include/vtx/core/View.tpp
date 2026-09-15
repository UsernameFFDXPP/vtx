#include"vtx/core/View.hpp"

namespace vtx{
    template<typename VType>
    Expression<VType>::Expression(const Matrix<VType> *mat):
        root_(std::make_shared<MatNode<value_type>>(Operation::Mat,mat)){}

    template<typename VType>
    Expression<VType>::Expression(Operation opr,const Expression<VType> &expr):
        root_(std::make_shared<UnaryNode<value_type>>(opr,expr.root_)){}

    template<typename VType>
    Expression<VType>::Expression(Operation opr,const Expression<VType> &lexpr,const Expression<VType> &rexpr):
        root_(std::make_shared<BinaryNode<value_type>>(opr,lexpr.root_,rexpr.root_)){}

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
    bool Expression<VType>::useTempRsl() const{
        return useTempRsl_;
    }

    template<typename VType>
    void Expression<VType>::setTempRsl(bool set){
        useTempRsl_=set;
        return;
    }

    template<typename VType>
    View<VType>::View(const Matrix<VType> *mat):
        expr_(mat){}

    template<typename VType>
    View<VType>::View(Operation opr,const View<VType> &view):
        expr_(opr,view.expr_){}

    template<typename VType>
    View<VType>::View(Operation opr,const View<VType> &lhs,const View<VType> &rhs):
        expr_(opr,lhs.expr_,rhs.expr_){}

    template<typename VType>
    VType View<VType>::operator()(std::size_t row,std::size_t col) const{
        return expr_.evalAt(row,col);
    }

    template<typename VType>
    Matrix<VType> View<VType>::eval() const{
        return expr_.eval();
    }
}