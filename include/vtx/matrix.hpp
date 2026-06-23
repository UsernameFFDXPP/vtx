#pragma once
#include<vector>
#include<cmath>
#include<limits>
#include<functional>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<stdexcept>

#include"vtx\Vector.hpp"

namespace vtx{
    class Range;

    template<typename VType>
    class Vector;

    template<typename VType>
    class Matrix{
        public:
            using CType=VType;

            using iterator=typename std::vector<Vector<VType>>::iterator;
            using const_iterator=typename std::vector<Vector<VType>>::const_iterator;

            /*Core*/
            Matrix();
            explicit Matrix(const std::vector<std::vector<VType>> &vct);
            explicit Matrix(size_t r,size_t c,VType value=VType{});
            Matrix(const Matrix<VType> &other);
            Matrix(std::initializer_list<std::initializer_list<VType>> init);
            ~Matrix();

            Vector<VType> &operator[](size_t i);
            const Vector<VType> &operator[](size_t i) const;
            size_t rowLength() const;
            size_t columnLength() const;
            const std::vector<Vector<VType>> &data() const;
            
            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;

            /*Operator*/
            Matrix<VType> &operator=(const Matrix<VType> &other);
            Matrix<VType> operator+(const Matrix<VType> &other) const;
            Matrix<VType> operator-(const Matrix<VType> &other) const;
            Matrix<VType> operator-() const;
            Matrix<VType> operator*(CType s) const;
            template<typename UType>
            friend Matrix<UType> operator*(typename Matrix<UType>::CType s, const Matrix<UType> &self);
            template<typename UType>
            friend std::ostream &operator<<(std::ostream &os, const Matrix<UType> &self);
            Matrix<VType> &operator+=(const Matrix<VType> &other);
            Matrix<VType> &operator-=(const Matrix<VType> &other);
            Matrix<VType> &operator*=(CType s);
            Matrix<VType> operator*(const Matrix<VType> &other) const;
            Matrix<VType> operator*(const Vector<VType> &other) const;

            /*Function*/
            std::vector<Vector<VType>> toVector(bool isColumn) const;
            Matrix<VType> combine(const Matrix<VType> &other,std::function<VType(VType,VType)> func) const;
            Matrix<VType> combine(const Vector<VType> &vct,std::function<VType(VType,VType)> func) const;
            Matrix<VType> trans(bool isMaindiag=true) const;
            Matrix<VType> flip(bool isVertical=true) const;
            Matrix<VType> swap(size_t idx1,size_t idx2,bool isVertical=true) const;
            Matrix<VType> slice(const Range &rRange,const Range &cRange) const;
            Matrix<VType> getDiag() const;
            Matrix<VType> getUTrig() const;
            Matrix<VType> getLTrig() const;
            
            VType det() const;
            
        private:
            size_t rowLength_;
            size_t columnLength_;
            std::vector<Vector<VType>> data_;
    };
}

#include"vtx/Matrix_Core.tpp"
#include"vtx/Matrix_Operator.tpp"
#include"vtx/Matrix_Function.tpp"