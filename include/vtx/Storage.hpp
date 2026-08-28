#pragma once

#include<vector>
#include<cstddef>

namespace vtx{
    template<typename VType>
    class Storage{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            Storage();
            explicit Storage(size_type size);

            size_type size() const;

            value_type& operator[](size_type index);
            const value_type& operator[](size_type index) const;

            value_type* data();
            const value_type* data() const;
        private:
            std::vector<value_type> data_;
    };
}