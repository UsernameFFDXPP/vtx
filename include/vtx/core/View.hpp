#pragma once

#include<cstddef>
#include<memory>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType>
    class View<Matrix<VType>>{
        public:
            using source_type=Matrix<VType>;
            using value_type=VType;
            using size_type=std::size_t;

            View(const Matrix<VType> *source,Axis axis=Axis::None,size_type index=0):
            source_(source),axis_(axis),index_(index){}

            size_type size() const{
                if(axis_==Axis::Row) return (*source_).colLength();
                else if(axis_==Axis::Col) return (*source_).rowLength();
                else{
                    /*Axis Error*/
                }
                return 0;
            }
            value_type operator()(size_type index) const{
                if(axis_==Axis::Row) return (*source_)(index_,index);
                else if(axis_==Axis::Col) return (*source_)(index,index_);
                else{
                    /*Axis Error*/
                }
                return {};
            }

        private:
            const Matrix<VType> *source_;
            Axis axis_;
            size_type index_;
    };
}//namespace vtx