#include"vtx/Range.hpp"
#include"vtx/Vector.hpp"

namespace vtx{
    Range::Range(size_t l,size_t u,bool isNL,bool isNU):
        lower_(l),upper_(u),isNoLower_(isNL),isNoUpper_(isNU){}
    Range::Range(std::initializer_list<int> init){
        intInit(init.begin()[0],init.begin()[1]);
    }
    Range::Range(vtx::Vector<int> v){
        intInit(v[0],v[1]);
    }
    
    size_t Range::lower() const{return lower_;}
    size_t Range::upper() const{return upper_;}
    bool Range::isNoLower() const{return isNoLower_;}
    bool Range::isNoUpper() const{return isNoUpper_;}

    Range Range::all(){
        return Range(0,0,true,true);
    }
    Range Range::from(size_t l){
        return Range(l,0,false,true);
    }
    Range Range::to(size_t u){
        return Range(0,u,true,false);
    }

    bool Range::isRangeUndefined() const{
        return isNoLower_||isNoUpper_;
    }
    size_t Range::length() const{
        if(this->isRangeUndefined()){

        }
        return lower_>upper_?lower_-upper_:upper_-lower_;
    }

    void Range::intInit(int l,int u){
        isNoLower_=(l<0);
        isNoUpper_=(u<0);
        lower_=isNoLower_?0:static_cast<size_t>(l);
        upper_=isNoLower_?0:static_cast<size_t>(u);
    }
}