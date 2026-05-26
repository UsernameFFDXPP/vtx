#pragma once
#include<vector>
#include<cmath>
#include<limits>
#include<functional>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<stdexcept>

#include<vtx\Vector.hpp>

namespace vtx{
    class Range;

    template<typename T>
    class Vector;

    template<typename T>
    class Matrix{
        public:
            using vtype=T;
            using ctype=T;

            using iterator=typename std::vector<Vector<T>>::iterator;
            using const_iterator=typename std::vector<Vector<T>>::const_iterator;

            Matrix();
            explicit Matrix(const std::vector<std::vector<vtype>> &vct);
            explicit Matrix(size_t r,size_t c,vtype value=T{});
            Matrix(const Matrix<T> &other);
            Matrix(std::initializer_list<std::initializer_list<vtype>> init);
            ~Matrix();

            Vector<T> &operator[](size_t i);
            const Vector<T> &operator[](size_t i) const;
            size_t rowLength() const;
            size_t columnLength() const;
            const std::vector<Vector<T>> &data() const;

            Matrix<T> &operator=(const Matrix<T> &other);
            Matrix<T> operator+(const Matrix<T> &other) const;
            Matrix<T> operator-(const Matrix<T> &other) const;
            Matrix<T> operator*(ctype s) const;
            template<typename U>
            friend Matrix<U> operator*(typename Matrix<U>::ctype s, const Matrix<U> &self);
            template<typename U>
            friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &self);
            Matrix<T> operator*(const Matrix<T> &other) const;
            Matrix<T> operator*(const Vector<T> &other) const;

            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;

            std::vector<Vector<T>> toVector(bool isColumn) const;
            Matrix<T> combine(const Matrix<T> &other,std::function<vtype(vtype,vtype)> func) const;
            Matrix<T> combine(const Vector<T> &vct,std::function<vtype(vtype,vtype)> func) const;
            Matrix<T> trans(bool isMaindiag=true) const;
            Matrix<T> flip(bool isVertical=true) const;
            Matrix<T> slice(const Range &rRange,const Range &cRange) const;
            Matrix<T> getDiag() const;
            Matrix<T> getUTrig() const;
            Matrix<T> getLTrig() const;
            
            vtype det() const;
            
        private:
            size_t rowLength_;
            size_t columnLength_;
            std::vector<Vector<T>> data_;
    };
}

#include"vtx/Matrix.tpp"