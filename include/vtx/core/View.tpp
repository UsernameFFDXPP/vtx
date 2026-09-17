#include"vtx/core/View.hpp"

namespace vtx{
    template<typename Source>
    View<Source>::View(const Source *source,Axis axis,size_type index):
        source_(source),axis_(axis),index_(index){}

    template<typename Source>
    std::size_t View<Source>::size() const{
        if(axis_==Axis::Row){
            return (*source_).colLength();
        }else if(axis_==Axis::Col){
            return (*source_).rowLength();
        }else{
            /*Axis Error*/
        }
        return 0;
    }

    template<typename Source>
    typename View<Source>::value_type View<Source>::operator()(size_type index) const{
        if(axis_==Axis::Row){
            return (*source_)(index_,index);
        }else if(axis_==Axis::Col){
            return (*source_)(index,index_);
        }else{
            /*Axis Error*/
        }
        return {};
    }
}