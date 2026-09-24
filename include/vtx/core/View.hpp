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

            View(const Source *source,Axis axis=Axis::None,size_type index=0):
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
            const Source *source_;
            Axis axis_;
            size_type index_;
    };
}//namespace vtx