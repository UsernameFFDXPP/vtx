#pragma once

#include<cstddef>
#include"vtx/core/Storage.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType>
    class Matrix{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            using storage_type=Storage<value_type>;
            using reference=typename storage_type::reference;
            using const_reference=typename storage_type::const_reference;

            Matrix();
            explicit Matrix(size_type rowLength,size_type colLength,value_type val=VType{});

            static Matrix zeros(size_type rowLength,size_type colLength);
            static Matrix ones(size_type rowLength,size_type colLength);
            static Matrix identity(size_type length);

            size_type rowLength() const;
            size_type colLength() const;
            size_type size() const;
            bool isEmpty() const;

            reference operator()(size_type idx);
            const_reference operator()(size_type idx) const;
            reference operator()(size_type row,size_type col);
            const_reference operator()(size_type row,size_type col) const;
            
        private:
            size_type rowLength_=0;
            size_type colLength_=0;
            Storage<value_type> data_;
    };
}//namespace vtx

#include"Matrix.tpp"