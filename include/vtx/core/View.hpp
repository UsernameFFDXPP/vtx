#pragma once

#include<cstddef>
#include<memory>
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType> class View;

    template<typename Source>
    class View{
        public:
            using source_type=Source;
            using value_type=typename Source::value_type;
            using size_type=std::size_t;

            View(const Source *source,Axis axis=Axis::None,std::size_t index=0):
            source_(source),axis_(axis),index_(index){}

            std::size_t size() const{
                return axis_==Axis::Row?(*source_).colLength()
                    :axis_==Axis::Col?(*source_).rowLength()
                    :axis_==Axis::None?(*source_).rowLength()*(*source_).colLength()
                    :0;
            }
            std::size_t rowLength() const{
                return axis_==Axis::Row?1
                    :axis_==Axis::Col?(*source_).rowLength()
                    :axis_==Axis::None?(*source_).rowLength()
                    :0;
            }
            std::size_t colLength() const{
                return axis_==Axis::Row?(*source_).colLength()
                    :axis_==Axis::Col?1
                    :axis_==Axis::None?(*source_).colLength()
                    :0;
            }

            value_type operator()(std::size_t index) const{
                if(axis_==Axis::Row) return (*source_)(index_,index);
                else if(axis_==Axis::Col) return (*source_)(index,index_);
                else if(axis_==Axis::None) return (*source_)(index%(*source_).colLength(),index/(*source_).colLength());
                else /*Axis Error*/;
                return {};
            }
            value_type operator()(std::size_t row,std::size_t col) const{
                if(axis_==Axis::None) return (*source_)(row,col);
                else /*Axis Error*/;
                return {};
            }

        private:
            const Source *source_;
            Axis axis_;
            std::size_t index_;
    };
}//namespace vtx