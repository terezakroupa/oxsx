#ifndef __OXSX__CONTAINER_TOOLS__
#define __OXSX__CONTAINER_TOOLS__
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <cassert>


template <typename T1, typename T2>
std::map<T1, T2> VecsToMap(const std::vector<T1>& v1_, const std::vector<T2>& v2_){
    assert(v1_.size() == v2_.size());
    
    std::map<T1, T2> map;
    for(size_t i = 0; i < v1_.size(); i++)
        map[v1_.at(i)] = v2_.at(i);
    return map;
}

template<typename T1, typename T2>
std::vector<T1> GetKeys(const std::map<T1, T2> & mp_){
    typedef typename std::map<T1, T2>::const_iterator mapIt;

    std::vector<T1> vec;
    vec.reserve(mp_.size());
    for(mapIt it = mp_.begin(); it != mp_.end(); ++it){
        vec.push_back(it->first);        
    }
    return vec;
}


template<typename T1, typename T2>
std::vector<T2> GetValues(const std::map<T1, T2>& mp_){
    typedef typename std::map<T1, T2>::const_iterator mapIt;

    std::vector<T2> vec;
    vec.reserve(mp_.size());
    for(mapIt it = mp_.begin(); it != mp_.end(); ++it){
        vec.push_back(it->second);        
    }
    return vec;
}

template<typename T1, typename T2>
bool HasSameKeys(const T1& m1_, const T2& m2_){
    return GetKeys(m1_) == GetKeys(m2_);
}

template<typename T1, typename T2>
bool HasKey(const std::map<T1, T2>& mp_, const T1& key_){    
    return mp_.find(key_) != mp_.end();
}


template<typename T1, typename T2, typename T3>
std::string CompareKeys(const std::map<T1, T2>& m1_, const std::map<T1, T3>& m2_, const std::string name1_ = "p1", const std::string& name2_ = "p2"){
    // nothing doing
    if(HasSameKeys(m1_, m2_))
        return name1_ + " and " + name2_ + " have the same keys";

    typename std::vector<T1> missingFrom1;
    typename std::vector<T1> missingFrom2;
    
    typedef typename std::map<T1, T2>::const_iterator mapIt2;
    typedef typename std::map<T1, T3>::const_iterator mapIt3;

    for(mapIt2 it = m1_.begin(); it != m1_.end(); ++it){
        if(!HasKey(m2_, it->first))
            missingFrom2.push_back(it->first);
    }

    std::string returnStr =  "Keys in " + name1_ + "Missing from " + name2_ + " : \n";
    for(size_t i = 0; i < missingFrom2.size(); i++){
        returnStr += std::string(missingFrom2.at(i));
        returnStr += ",";
    }

    returnStr += "\n";
    return returnStr;
}

template<typename T1>
std::string ToString(const T1& c_, const std::string& delimit_ = ", "){
    std::string retStr = "";
    for(typename T1::const_iterator it = c_.begin(); it != c_.end(); ++it)
        retStr += std::string(*it) + delimit_;
    return retStr;
}


#endif
