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

    template<typename VType>
    class Matrix;

    template<typename VType>
    class Vector{
        public:
            using CType=VType;

            using iterator=typename std::vector<VType>::iterator;
            using const_iterator=typename std::vector<VType>::const_iterator;

            /*Core*/
            Vector();
            explicit Vector(const std::vector<VType> &vct,bool isCol=true);
            explicit Vector(bool isColumn);
            explicit Vector(size_t length,bool isCol=true,VType value=VType{});
            Vector(const Vector<VType> &other);
            Vector(std::initializer_list<VType> init,bool isColumn=true);
            ~Vector();

            VType &operator[](size_t i);
            const VType &operator[](size_t i) const;
            size_t length() const;
            bool isColumn() const;
            const std::vector<VType> &data() const;

            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;

            /*Operator*/
            Vector<VType> &operator=(const Vector<VType> &other);
            Vector<VType> operator+(const Vector<VType> &other) const;
            Vector<VType> operator-(const Vector<VType> &other) const;
            Vector<VType> operator-() const;
            Vector<VType> operator*(CType s) const;
            template<typename U>
            friend Vector<U> operator*(typename Vector<U>::CType s, const Vector<U> &self);
            template<typename U>
            friend std::ostream &operator<<(std::ostream &os, const Vector<U> &self);
            Vector<VType> &operator+=(const Vector<VType> &other);
            Vector<VType> &operator-=(const Vector<VType> &other);
            Vector<VType> &operator*=(CType s);
            Matrix<VType> operator*(const Vector<VType> &other) const;
            Matrix<VType> operator*(const Matrix<VType> &other) const;

            /*Function*/
            Matrix<VType> toMatrix() const;
            Vector<VType> combine(const Vector<VType> &other,std::function<VType(VType,VType)>)const;
            Vector<VType> trans() const;
            Vector<VType> flip() const;
            Vector<VType> swap(size_t idx1,size_t idx2) const;
            Vector<VType> slice(const Range &range) const;
            VType norm(double p);
        private:
            size_t length_;
            bool isColumn_;
            std::vector<VType> data_;
    };
}

#include"vtx/Vector_Core.tpp"
#include"vtx/Vector_Operator.tpp"
#include"vtx/Vector_Function.tpp"