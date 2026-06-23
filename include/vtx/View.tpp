#include"vtx/View.hpp"

namespace vtx{
    namespace internal{
        template<typename VType,typename FuncNode>
        void ASTVisiter(const ASTNodePtr<VType> &node,FuncNode &func);
        template<typename VType>
        RPNNode<VType> ASTNodeToRPNNode(const ASTNodePtr<VType> &node);
    }

    template<typename VType>
    View<VType>::View()=default;
    template<typename VType>
    View<VType>::View(const Matrix<VType> *mat){
        root_=std::make_shared<ASTNode<VType>>(ASTNode<VType>{
            ASTOp::Mat,
            {},
            ASTMat<VType>{mat}
        });
    }
    template<typename VType>
    View<VType>::View(const ASTNodePtr<VType> node):
        root_(node){}
    template<typename VType>
    View<VType>::~View()=default;

    template<typename VType>
    View<VType> &View<VType>::operator=(const View<VType> &other){
        root_=other.root_;
        return *this;
    }
    template<typename VType>
    View<VType> View<VType>::operator+(const View<VType> &other) const{
        ASTNodePtr<VType> rslNodePtr=std::make_shared<ASTNode<VType>>(ASTNode<VType>{
            ASTOp::Add,
            std::vector<ASTNodePtr<VType>>{root_,other.root_},
            ASTMat<VType>{}
    });
        View<VType> rslView{rslNodePtr};
        return rslView;
    }
    template<typename VType>
    View<VType> View<VType>::operator-(const View<VType> &other) const{
        ASTNodePtr<VType> tempNodePtr=std::make_shared<ASTNode<VType>>(ASTNode<VType>{
            ASTOp::Neg,
            std::vector<ASTNodePtr<VType>>{other.root_},
            ASTMat<VType>{}
        });
        ASTNodePtr<VType> rslNodePtr=std::make_shared<ASTNode<VType>>(ASTNode<VType>{
            ASTOp::Add,
            std::vector<ASTNodePtr<VType>>{root_,tempNodePtr},
            ASTMat<VType>{}
        });
        View<VType> rslView{rslNodePtr};
        return rslView;
    }
    template<typename VType>
    View<VType> View<VType>::operator*(const View<VType> &other) const{
        ASTNodePtr<VType> rslNodePtr=std::make_shared<ASTNode<VType>>(ASTNode<VType>{
            ASTOp::Mul,
            std::vector<ASTNodePtr<VType>>{root_,other.root_},
            ASTMat<VType>{}
        });
        View<VType> rslView{rslNodePtr};
        return rslView;
    }

    template<typename VType>
    ViewCache<VType> View<VType>::toCache(){
        ViewCache<VType> rslViewCache;

        auto emit=[&rslViewCache](const ASTNodePtr<VType> &node){
            rslViewCache.pushInPlace(internal::ASTNodeToRPNNode(node));
        };
        internal::ASTVisiter(root_,emit);
        return rslViewCache;
    }

    namespace internal{
        template<typename VType,typename FuncNode>
        void ASTVisiter(const ASTNodePtr<VType> &node,FuncNode &func){
            if(!node) return;
            for(auto &childnode:node->children){
                ASTVisiter(childnode,func);
            }
            func(node);
            return;
        }

        template<typename VType>
        RPNNode<VType> ASTNodeToRPNNode(const ASTNodePtr<VType> &node){
            if(node->type==ASTOp::Mat){
                return RPNNode<VType>{RPNOp::Mat,node->matNode.mat};
            }else if(node->type==ASTOp::Add){
                return RPNNode<VType>{RPNOp::Add,nullptr};
            }else if(node->type==ASTOp::Neg){
                return RPNNode<VType>{RPNOp::Neg,nullptr};
            }else if(node->type==ASTOp::Mul){
                return RPNNode<VType>{RPNOp::Mul,nullptr};
            }else if(node->type==ASTOp::Inv){
                return RPNNode<VType>{RPNOp::Inv,nullptr};
            }else if(node->type==ASTOp::Trans){
                return RPNNode<VType>{RPNOp::Trans,nullptr};
            }
            return RPNNode<VType>{RPNOp::Mat,nullptr};
        }
    }
}