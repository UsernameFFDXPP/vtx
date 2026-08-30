#pragma once

#include<cstddef>
#include"vtx/core/Matrix.hpp"
#include"vtx/core/Axis.hpp"

namespace vtx{
    template<typename VType>
    Matrix<VType> sum(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> max(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> min(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<std::size_t> argmax(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<std::size_t> argmin(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> mean(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> variance(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> mediam(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> quantile(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> covariance(const Matrix<VType> &mat,Axis axis=Axis::None);

    template<typename VType>
    Matrix<VType> correlation(const Matrix<VType> &mat,Axis axis=Axis::None);
}