#include <Exceptions.h>
#include <vector>
#include <utility>
#include <assert.h>
#include <set>
#include <iostream>

namespace Combinations{
	
	void
	RecursiveCombinations(size_t depth, std::vector< std::vector<size_t> >& combs, std::vector<size_t> vec, std::vector<size_t> maxes_){


		std::cout << "RecrusiveCombinations depth" << depth <<std::endl;
		if (depth>0){
			std::cout << "RecrusiveCombinations maxes_[depth-1]" << maxes_[depth-1] <<std::endl;
			for(size_t i=0; i<maxes_[depth-1]; i++){
				vec[depth-1] = i;
				RecursiveCombinations(depth-1, combs, vec, maxes_);
			}
			
	}else{
			combs.push_back(vec);
		}
		
	return;
	}
	
}
