#pragma once
#include<variant>
#include<memory>
#include<stdexcept>
#include<vector>

namespace vtx{
    enum class RPNOp{
        Mat,
        Add,
        Neg,
        Mul,
        Inv,
        Trans
    };

    template<typename VType>
    class Matrix;
    template<typename VType>
    struct RPNNode;
    template<typename VType>
    class ViewCache;

    template<typename VType>
    struct RPNNode{
        RPNOp type;
        const Matrix<VType> *mat;
    };

    template<typename VType>
    class ViewCache{
        public:
            ViewCache();
            ViewCache(const Matrix<VType> *mat);
            ~ViewCache();

            ViewCache<VType> &operator=(const ViewCache<VType> &other);
            ViewCache<VType> operator+(const ViewCache<VType> &other) const;
            ViewCache<VType> operator-(const ViewCache<VType> &other) const;
            ViewCache<VType> operator*(const ViewCache<VType> &other) const;

            ViewCache<VType> trans() const;

            ViewCache<VType> &pushInPlace(const RPNNode<VType> &node);
            Matrix<VType> eval();
        private:
            std::vector<RPNNode<VType>> expr_;
    };
}

#include"vtx/View_Cache.tpp"