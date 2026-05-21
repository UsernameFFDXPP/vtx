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
    class Vector;
    class Matrix{
        public:
            using vtype=double;
            using ctype=double;

            Matrix();
            Matrix(const std::vector<std::vector<vtype>> &vct);
            Matrix(size_t r,size_t c,vtype v=0.0);
            Matrix(const Matrix &other);
            Matrix(std::initializer_list<std::initializer_list<vtype>> init);
            ~Matrix();

            Vector &operator[](size_t i);
            const Vector &operator[](size_t i) const;
            size_t rowLength() const;
            size_t columnLength() const;
            const std::vector<Vector> &data() const;

            Matrix &operator=(const Matrix &other);
            Matrix operator+(const Matrix &other) const;
            Matrix operator-(const Matrix &other) const;
            Matrix operator*(ctype s) const;
            friend Matrix operator*(ctype s,const Matrix &self);
            friend std::ostream &operator<<(std::ostream &os,const Matrix &self);
            Matrix operator*(const Matrix &other) const;
            Matrix operator*(const Vector &other) const;

            std::vector<Vector> toVector(bool isColumn) const;
            Matrix iter(Matrix &other,std::function<vtype(vtype,vtype)> func) const;
            Matrix iter(Vector &vct,std::function<vtype(vtype,vtype)> func) const;
            Matrix trans(bool isMaindiag=true) const;
            Matrix flip(bool isVertical=true) const;
            Matrix getDiag() const;
            Matrix getUTrig() const;
            Matrix getLTrig() const;
            
            vtype det() const;
            
        private:
            size_t rowLength_;
            size_t columnLength_;
            std::vector<Vector> data_;
    };
}
