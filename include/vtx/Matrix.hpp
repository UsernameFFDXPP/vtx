#pragma once

#include<cstddef>
#include"Storage.hpp"

namespace vtx{
    template<typename VType>
    class Matrix{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            Matrix();
            explicit Matrix(size_type rowLength,size_type colLength);

            size_type rowLength() const;
            size_type colLength() const;

            value_type &operator()(size_type row,size_type col);
            const value_type &operator()(size_type row,size_type col) const;

        private:
            size_type rowLength_;
            size_type colLength_;
            Storage<value_type> data_;
    };
}