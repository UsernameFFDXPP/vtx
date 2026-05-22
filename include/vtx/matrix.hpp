#pragma once
#include<vector>
#include<cmath>
#include<limits>
#include<functional>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<stdexcept>

#include<vtx\vector.hpp>

namespace vtx{
    template<typename T>
    class Vector;
    template<typename T>
    class Matrix{
        public:
            using vtype=T;
            using ctype=T;

            Matrix();
            Matrix(const std::vector<std::vector<vtype>> &vct);
            Matrix(size_t r,size_t c,vtype v=0.0);
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

            std::vector<Vector<T>> toVector(bool isColumn) const;
            Matrix<T> iter(Matrix<T> &other,std::function<vtype(vtype,vtype)> func) const;
            Matrix<T> iter(Vector<T> &vct,std::function<vtype(vtype,vtype)> func) const;
            Matrix<T> trans(bool isMaindiag=true) const;
            Matrix<T> flip(bool isVertical=true) const;
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

#include"vtx/matrix.tpp"