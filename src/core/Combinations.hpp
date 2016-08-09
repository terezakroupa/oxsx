#ifndef __OXSX_COMBINATIONS__
#define __OXSX_COMBINATIONS__
#include <vector>
#include <Exceptions.h>

template<typename T>
std::vector<std::vector<T> >
AllCombinations(const std::vector<T>& vals_){
  typedef std::vector<std::vector<T> > TVecVec;
  typedef std::vector<T> TVec;

  TVecVec allCombs;  
  for(size_t i = 1; i < vals_.size(); i++){
	TVecVec iLengthCombs = FixedLengthCombinations(vals_, i);
	allCombs.insert(allCombs.end(), iLengthCombs.begin(), iLengthCombs.end());
  }
  return allCombs;
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
	TVecVec reducedCombs = FixedLengthCombinations(vals_, nElements_ - 1);
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
#endif
