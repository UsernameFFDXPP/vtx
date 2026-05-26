#pragma once
#include<vector>
#include<cmath>
#include<limits>
#include<functional>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<stdexcept>

#include"vtx/Matrix.hpp"

namespace vtx{
    class Range;

    template<typename T>
    class Matrix;

    template<typename T>
    class Vector{
        public:
            using vtype=T;
            using ctype=T;

            using iterator=typename std::vector<T>::iterator;
            using const_iterator=typename std::vector<T>::const_iterator;

            Vector();
            explicit Vector(const std::vector<vtype> &vct,bool isCol=true);
            explicit Vector(bool isColumn);
            explicit Vector(size_t length,bool isCol=true,vtype value=T{});
            Vector(const Vector<T> &other);
            Vector(std::initializer_list<vtype> init,bool isColumn=true);
            ~Vector();

            vtype &operator[](size_t i);
            const vtype &operator[](size_t i) const;
            size_t length() const;
            bool isColumn() const;
            const std::vector<vtype> &data() const;

            Vector<T> &operator=(const Vector<T> &other);
            Vector<T> operator+(const Vector<T> &other) const;
            Vector<T> operator-(const Vector<T> &other) const;
            Vector<T> operator*(ctype s) const;
            template<typename U>
            friend Vector<U> operator*(typename Vector<U>::ctype s, const Vector<U> &self);
            template<typename U>
            friend std::ostream &operator<<(std::ostream &os, const Vector<U> &self);
            Vector<T> &operator+=(const Vector<T> &other);
            Vector<T> &operator-=(const Vector<T> &other);
            Vector<T> &operator*=(ctype s);
            Matrix<T> operator*(const Vector<T> &other) const;
            Matrix<T> operator*(const Matrix<T> &other) const;

            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;

            Matrix<T> toMatrix() const;
            Vector<T> combine(Vector<T> &other,std::function<vtype(vtype,vtype)>)const;
            Vector<T> trans() const;
            Vector<T> flip() const;
            Vector<T> slice(const Range &range) const;
            vtype norm(const double &p) const;
        private:
            size_t length_;
            bool isColumn_;
            std::vector<vtype> data_;
    };
}

#include"vtx/Vector.tpp"