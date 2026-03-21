#pragma once

#include <vector>
#include <algorithm>

template<class DATA_TYPE, class ALLOCATOR = std::allocator<DATA_TYPE>>
class ZArray : public std::vector<DATA_TYPE, ALLOCATOR>
{
	using value_type = std::vector<DATA_TYPE, ALLOCATOR>::value_type  ;
public:

	//return new elem index if added, else return current num of elem
	inline int AddUnique(DATA_TYPE elem) {
		int Num = this->size();
		auto it = std::find(this->begin(), this->end(), elem);
		if (it == this->end())
		{
			this->push_back(elem);
			return Num;
		}
		return --Num;
	};

};
