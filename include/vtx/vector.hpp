#pragma once
#include<vector>
#include<cmath>
#include<limits>
#include<functional>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<stdexcept>

#include"vtx/matrix.hpp"

namespace vtx{
    class Matrix;
    class Vector{
        public:
            using vtype=double;
            using ctype=double;

            Vector(bool isColumn=true);
            Vector(const std::vector<vtype> &vct,bool isCol=true);
            Vector(size_t length,bool isCol=true,vtype value=0.0);
            Vector(const Vector &other);
            Vector(std::initializer_list<vtype> init,bool isColumn=true);
            ~Vector();

            vtype &operator[](size_t i);
            const vtype &operator[](size_t i) const;
            size_t length() const;
            bool isColumn() const;
            const std::vector<vtype> &data() const;

            Vector &operator=(const Vector &other);
            Vector operator+(const Vector &other) const;
            Vector operator-(const Vector &other) const;
            Vector operator*(ctype s) const;
            friend Vector operator*(ctype s,const Vector &self);
            friend std::ostream &operator<<(std::ostream &os,const Vector &self);
            Vector &operator+=(const Vector &other);
            Vector &operator-=(const Vector &other);
            Vector &operator*=(ctype s);
            Matrix operator*(const Vector &other) const;
            Matrix operator*(const Matrix &other) const;

            Matrix toMatrix() const;
            Vector iter(Vector &other,std::function<vtype(vtype,vtype)>)const;
            Vector trans() const;
            Vector flip() const;
            vtype norm(const double &p) const;
        private:
            size_t length_;
            bool isColumn_;
            std::vector<vtype> data_;
    };
}
