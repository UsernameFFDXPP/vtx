#pragma once

#include<vector>
#include<cstddef>
#include<cstdint>

namespace vtx{
    template<typename VType>
    class Storage{
        public:
            using value_type=VType;
            using size_type=std::size_t;

            using reference=value_type&;
            using const_reference=const value_type&;

            using iterator=typename std::vector<value_type>::iterator;
            using const_iterator=typename std::vector<value_type>::const_iterator;

            Storage()=default;
            explicit Storage(size_type size);

            size_type size() const;

            value_type &operator[](size_type index);
            const value_type &operator[](size_type index) const;

            iterator begin();
            const_iterator begin() const;

            iterator end();
            const_iterator end() const;

            void resize(size_type size);
        private:
            std::vector<value_type> data_;
    };

    template<>
    class Storage<bool>{
        public:
            using value_type=bool;
            using size_type=std::size_t;

            class reference{
                public:
                    reference(std::uint8_t &value):
                        value_(value){}
                    reference &operator=(bool value){
                        value_=value?1:0;
                        return *this;
                    }
                    reference &operator=(const reference &other){
                        return *this=static_cast<bool>(other);
                    }
                    operator bool() const{
                        return value_!=0;
                    }      
                private:
                    std::uint8_t &value_;
            };
            using const_reference=bool;

            using iterator=typename std::vector<value_type>::iterator;
            using const_iterator=typename std::vector<value_type>::const_iterator;

            Storage()=default;
            explicit Storage(size_type size):
                data_(size){}

            size_type size() const{
                return data_.size();
            }

            reference operator[](size_type index){
                return reference(data_[index]);
            }
            const_reference operator[](size_type index) const{
                return data_[index]!=0;
            }
            /*
            iterator begin(){
                return data_.begin();
            }
            const_iterator begin() const{
                return data_.cbegin();
            }

            iterator end(){
                return data_.end();
            }
            const_iterator end() const{
                return data_.cend();
            }
            */
            void resize(size_type size){
                data_.resize(size);
            }
        private:
            std::vector<std::uint8_t> data_;
    };
}

#include"Storage.tpp"