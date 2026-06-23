#pragma once
#include<stdexcept>

namespace vtx{
    template<typename VType>
    class Vector;
    class Range{
        public:
            Range(size_t l,size_t u,bool isNL=false,bool isNU=false);
            Range(std::initializer_list<int> init);
            Range(vtx::Vector<int> v);

            size_t lower() const;
            size_t upper() const;
            bool isNoLower() const;
            bool isNoUpper() const;

            static Range all();
            static Range from(size_t l);
            static Range to(size_t u);

            bool isRangeUndefined() const;
            size_t length() const;
            
        private:
            size_t lower_;
            size_t upper_;
            bool isNoLower_;
            bool isNoUpper_;

            void intInit(int l,int u);
    };
}