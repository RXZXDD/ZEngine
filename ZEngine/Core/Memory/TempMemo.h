#pragma once

#include <vector>

namespace ZEngine
{
	template<typename T>
	class TempMemo
	{
		std::vector<T> Data;
	public:
		TempMemo() = default;
		~TempMemo() = default;
		void Add(const T& item) {
			Data.push_back(item);
		}
		const std::vector<T>& GetData() const {
			return Data;
		}
		void Clear() {
			Data.clear();
		}
	};
}
