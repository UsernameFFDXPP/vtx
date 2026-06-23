#pragma once
#include<variant>
#include<memory>
#include<stdexcept>
#include<vector>
#include"vtx/View_Cache.hpp"

namespace vtx{
    enum class ASTOp{
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
    struct ASTNode;
    template<typename VType>
    struct ASTMat;

    template<typename VType>
    using ASTNodePtr=std::shared_ptr<ASTNode<VType>>;
    template<typename VType>
    using ASTMatPtr=std::shared_ptr<ASTMat<VType>>;
    
    template<typename VType>
    struct ASTMat{
        const Matrix<VType> *mat;
    };

    template<typename VType>
    struct ASTNode{
        ASTOp type;
        std::vector<ASTNodePtr<VType>> children;
        ASTMat<VType> matNode;
    };

    template<typename VType>
    class View{
        public:
            View();
            View(const Matrix<VType> *mat);
            View(const ASTNodePtr<VType> node);
            ~View();

            View<VType> &operator=(const View<VType> &other);
            View<VType> operator+(const View<VType> &other) const;
            View<VType> operator-(const View<VType> &other) const;
            View<VType> operator*(const View<VType> &other) const;

            Matrix<VType> eval();
            ViewCache<VType> toCache();
        private:
            ASTNodePtr<VType> root_;
    };
}

#include"vtx/View.tpp"