#pragma once

#include <Helper/HelperMacro.h>

#include <vector>
#include <cassert>

template<class DATA_TYPE>
class ZRingBuffer 
{
	std::vector<DATA_TYPE> m_data;

	size_t pHead = 0;
	size_t pTail = 0;
	size_t Capacity = 0;

	ZRingBuffer(const ZRingBuffer&) = delete;
	ZRingBuffer& operator=(const ZRingBuffer&) = delete;


public:

	ZRingBuffer(size_t capacity) { 
		m_data.resize(capacity);
		Capacity = m_data.capacity();
		
	}
	~ZRingBuffer() {
		m_data.clear();
	};

	DATA_TYPE& operator[](size_t index)
	{
		assert(index < Capacity);
		return  m_data[index];
	}

	void Push(DATA_TYPE&& item)
	{
		//TODO move semantics if is unique ptr or other moveable type
		//m_data[pTail].reset();
		m_data.at(pTail) = std::forward<DATA_TYPE>(item);
		pTail = (pTail + 1) % Capacity;
		if (pTail == pHead) {
			pHead = (pHead + 1) % Capacity; // Overwrite the oldest item
		}
	}

	void Reset() {
		std::fill(m_data.begin(), m_data.end(), DATA_TYPE{});
		pHead = 0;
		pTail = 0;
	}

	DATA_TYPE& Tail() {
		return m_data[pTail-1];
	}
	size_t GetHeadIdx()const { return pHead; }
	size_t GetTailIdx()const { return pTail; }

	size_t GetNextIdx(size_t index)const {
		return (index + 1) % Capacity;
	}

	size_t GetCapacity() const { return Capacity; }
	size_t GetSize() const { return (pTail - pHead + Capacity)% Capacity; }
};


