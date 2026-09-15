#pragma once

#include"vtx/core/View.hpp"
#include"vtx/core/Operation.hpp"

namespace vtx{
    /*Neg*/
    template<typename VType>
    View<VType> neg(const View<VType> &view){
        return View(Operation::Neg,view);
    }
    /*EwiseInv*/
    template<typename VType>
    View<VType> ewiseInv(const View<VType> &view){
        return View(Operation::EwiseInv,view);
    }
    /*EwiseMul*/
    template<typename VType>
    View<VType> ewiseMul(const View<VType> &view,const VType &arg){
        return View(Operation::EwiseMul,view);/*?*/
    }
    /*EwiseDiv*/
    template<typename VType>
    View<VType> ewiseDiv(const View<VType> &view){
        return View(Operation::EwiseDiv,view);
    }
    /*EwiseMod*/
    template<typename VType>
    View<VType> ewiseMod(const View<VType> &view){
        return View(Operation::EwiseMod,view);
    }
    /*Add*/
    template<typename VType>
    View<VType> add(const View<VType> &lhs,const View<VType> &rhs){
        return View(Operation::Add,lhs,rhs);
    }
    /*Sub*/
    template<typename VType>
    View<VType> sub(const View<VType> &lhs,const View<VType> &rhs){
        return View(Operation::Sub,lhs,rhs);
    }
}