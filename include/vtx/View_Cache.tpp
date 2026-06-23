#include"vtx/View_Cache.hpp"

namespace vtx{
    template<typename VType>
    ViewCache<VType>::ViewCache()=default;
    template<typename VType>
    ViewCache<VType>::ViewCache(const Matrix<VType> *mat):
        expr_({RPNNode<VType>{RPNOp::Mat,mat}}){}
    template<typename VType>
    ViewCache<VType>::~ViewCache()=default;

    template<typename VType>
    ViewCache<VType> &ViewCache<VType>::operator=(const ViewCache<VType> &other){
        this->expr_=other.expr_;
        return *this;
    }
    template<typename VType>
    ViewCache<VType> ViewCache<VType>::operator+(const ViewCache<VType> &other) const{
        ViewCache<VType> rsl;
        rsl.expr_.insert(rsl.expr_.end(),this->expr_.begin(),this->expr_.end());
        rsl.expr_.insert(rsl.expr_.end(),other.expr_.begin(),other.expr_.end());
        rsl.expr_.push_back({RPNOp::Add,nullptr});
        return rsl;
    }
    template<typename VType>
    ViewCache<VType> ViewCache<VType>::operator-(const ViewCache<VType> &other) const{
        ViewCache<VType> rsl;
        rsl.expr_.insert(rsl.expr_.end(),this->expr_.begin(),this->expr_.end());
        rsl.expr_.insert(rsl.expr_.end(),other.expr_.begin(),other.expr_.end());
        rsl.expr_.push_back({RPNOp::Neg,nullptr});
        rsl.expr_.push_back({RPNOp::Add,nullptr});
        return rsl;
    }
    template<typename VType>
    ViewCache<VType> ViewCache<VType>::operator*(const ViewCache<VType> &other) const{
        ViewCache<VType> rsl;
        rsl.expr_.insert(rsl.expr_.end(),this->expr_.begin(),this->expr_.end());
        rsl.expr_.insert(rsl.expr_.end(),other.expr_.begin(),other.expr_.end());
        rsl.expr_.push_back({RPNOp::Mul,nullptr});
        return rsl;
    }

    template<typename VType>
    Matrix<VType> ViewCache<VType>::eval(){
        std::vector<Matrix<VType>> calStk;
        calStk.reserve(expr_.size());
        for(const auto &node:expr_){
            if(node.type==RPNOp::Mat){
                if(node.mat!=nullptr){
                    calStk.push_back(*node.mat);
                }else{
                    
                }
            }else if(node.type==RPNOp::Add){
                Matrix<VType> rhs=std::move(calStk.back());calStk.pop_back();
                Matrix<VType> lhs=std::move(calStk.back());calStk.pop_back();
                calStk.push_back(lhs+rhs);
            }else if(node.type==RPNOp::Neg){
                Matrix<VType> val=std::move(calStk.back());calStk.pop_back();
                calStk.push_back(-val);
            }else if(node.type==RPNOp::Mul){
                Matrix<VType> rhs=std::move(calStk.back());calStk.pop_back();
                Matrix<VType> lhs=std::move(calStk.back());calStk.pop_back();
                calStk.push_back(lhs*rhs);
            }else if(node.type==RPNOp::Inv){
                Matrix<VType> val=std::move(calStk.back());calStk.pop_back();
                ///calStk.push_back(-val);
            }
        }
        return std::move(calStk.back());
    }

    template<typename VType>
    ViewCache<VType> &ViewCache<VType>::pushInPlace(const RPNNode<VType> &node){
        expr_.push_back(node);
        return *this;
    }

    namespace internal{

    }
}