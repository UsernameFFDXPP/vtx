#pragma once

#include<cstddef>
#include<memory>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Expression.hpp"
#include"vtx/core/ASTNode.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType> class EvalVisitor;

    template<typename Source>
    class View{
        public:
            using source_type=Source;
            using value_type=typename Source::value_type;
            using size_type=std::size_t;

            View(const Source *source,Axis axis=Axis::None,size_type index=0);

            size_type size() const;
            value_type operator()(size_type index) const;

        private:
            const Source *source_;
            Axis axis_;
            size_type index_;
    };

    template<typename VType>
    class View<ASTNode<VType>>{
        public:
            using source_type=ASTNode<VType>;
            using value_type=VType;
            using size_type=std::size_t;

            View(const ASTNode<VType> *source,Axis axis=Axis::None,size_type index=0):
                source_(source),axis_(axis),index_(index){}

            size_type size() const{
                if(axis_==Axis::Row){
                    return (*source_).colLength();
                }else if(axis_==Axis::Col){
                    return (*source_).rowLength();
                }else{
                    /*Axis Error*/
                }
                return 0;
            }
            value_type operator()(size_type index) const{
                EvalVisitor<VType> visitor;
                if(axis_==Axis::Row){
                    return source_->accept(visitor,index_,index);
                }else if(axis_==Axis::Col){
                    return source_->accept(visitor,index,index_);
                }
                return {};
            }

        private:
            const ASTNode<VType> *source_;
            Axis axis_;
            size_type index_;
    };
}


#include"vtx/core/View.tpp"