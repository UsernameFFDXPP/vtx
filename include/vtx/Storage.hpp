#pragma once

#include<vector>
#include<cstddef>

namespace vtx{
    template<typename VType>
    class Storage{
        public:
            using value_type=VType;
            using size_type=std::size_t;
            using iterator=typename std::vector<value_type>::iterator;
            using const_iterator=typename std::vector<value_type>::const_iterator;

            Storage();
            explicit Storage(size_type size);

            size_type size() const;

            value_type &operator[](size_type index);
            const value_type &operator[](size_type index) const;

            iterator begin();
            const_iterator begin() const;

            iterator end();
            const_iterator end() const;
        private:
            std::vector<value_type> data_;
    };
}

#include"Storage.tpp"