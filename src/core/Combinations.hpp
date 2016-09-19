#ifndef __OXSX_COMBINATIONS__
#define __OXSX_COMBINATIONS__
#include <Exceptions.h>
#include <set>
#include <vector>

template<typename T>
std::vector<T>
SequentialElements(T init_, T nElements_){
  typedef std::vector<T> TVec;
  TVec returnVec;
  returnVec.reserve(nElements_);
  for(T i = init_; i < nElements_; i++){
    returnVec.push_back(i);
  }
  return returnVec;
}

template<typename T>
bool 
ContainsDuplicates(const std::vector<T>& vals_){
    std::set<T> s(vals_.begin(), vals_.end());
    return s.size() != vals_.size();
}

template<typename T>
std::vector<std::vector<T> >
FixedLengthCombinations(const std::vector<T>& vals_, int nElements_){
  typedef std::vector<std::vector<T> > TVecVec;
  typedef std::vector<T> TVec;

  if(!nElements_)
    throw ValueError("FixedLengthCombinations::Can't produce zero length combinations!");

  if(!vals_.size())
    throw ValueError("FixedLengthCombinations::Can't produce combinations from zero length vector!");

  TVecVec returnVec;
  if (nElements_ == 1){   
    for(size_t i = 0; i < vals_.size(); i++)
      returnVec.push_back(TVec(1, vals_.at(i)));
  } // nElements = 1

  else{
    TVecVec reducedCombs = FixedLengthCombinations<T>(vals_, nElements_ - 1);
    for(size_t i = 0; i < vals_.size(); i++){
      for(size_t j = 0; j < reducedCombs.size(); j++){
        TVec oneComb = reducedCombs.at(j);
        oneComb.push_back(vals_.at(i));
        returnVec.push_back(oneComb);
      }
    }
  } // nElements != 1

  return returnVec;
}

template<typename T>
std::vector<std::vector<T> >
FixedLengthCombinationsNoDuplicates(const std::vector<T>& vals_, int nElements_){
    std::vector<std::vector<size_t> > retVal;
    std::vector<std::vector<size_t> > withRepeats = FixedLengthCombinations<T>(vals_, nElements_);
    for(size_t i = 0; i < withRepeats.size(); i++){
        std::vector<size_t> combs = withRepeats.at(i);
        if(!ContainsDuplicates(combs))
            retVal.push_back(std::vector<T>(combs.begin(), combs.end()));
    }
    return retVal;
}



template<typename T>
std::vector<std::vector<T> >
AllCombinations(const std::vector<T>& vals_){
  typedef std::vector<std::vector<T> > TVecVec;
  typedef std::vector<T> TVec;

  TVecVec allCombs;  
  for(size_t i = 1; i < vals_.size(); i++){
    TVecVec iLengthCombs = FixedLengthCombinations<T>(vals_, i);
    allCombs.insert(allCombs.end(), iLengthCombs.begin(), iLengthCombs.end());
  }
  return allCombs;
}

template<typename T>
std::vector<std::vector<T> >
AllCombinationsNoDuplicates(const std::vector<T>& vals_){
    std::vector<std::vector<T> > retVal;
    std::vector<std::vector<T> > withRepeats = AllCombinations<T>(vals_);    
    for(size_t i = 0; i < withRepeats.size(); i++){
        std::vector<T> combs = withRepeats.at(i);
        if(!ContainsDuplicates(combs))
            retVal.push_back(std::vector<T>(combs.begin(), combs.end()));
    }
    return retVal;
}

template<typename T>
std::vector<std::vector<T> >
AllCombinationsShorterThan(const std::vector<T>& vals_, size_t maxLen_){
  typedef std::vector<std::vector<T> > TVecVec;
  typedef std::vector<T> TVec;
  
  TVecVec allCombs;  
  for(size_t i = 1; i <= maxLen_; i++){
    TVecVec iLengthCombs = FixedLengthCombinations<T>(vals_, i);
    allCombs.insert(allCombs.end(), iLengthCombs.begin(), iLengthCombs.end());
  }
  return allCombs;
}


template<typename T>
std::vector<std::vector<T> >
AllCombinationsShorterThanNoDuplicates(const std::vector<T>& vals_, size_t maxLen_){
  typedef std::vector<std::vector<T> > TVecVec;
  typedef std::vector<T> TVec;
  
  TVecVec allCombs;  
  for(size_t i = 1; i <= maxLen_; i++){
    TVecVec iLengthCombs = FixedLengthCombinationsNoDuplicates<T>(vals_, i);    
    allCombs.insert(allCombs.end(), iLengthCombs.begin(), iLengthCombs.end());
  }
  return allCombs;
}  
#endif
