#pragma once

#include <stdexcept>

#include "cuda_host_device.h"

template<typename T, unsigned int MaxSize>
class FixedSizeVector
{
public:
	_HOST_DEVICE_ FixedSizeVector() : m_size(0) { }

	inline _HOST_DEVICE_ bool empty() const { return m_size == 0; }
	inline _HOST_DEVICE_ bool full() const { return m_size >= MaxSize; }
	inline _HOST_DEVICE_ unsigned int size() const { return m_size; }
	inline _HOST_DEVICE_ unsigned int maxSize() const { return MaxSize; }

	inline _HOST_DEVICE_ bool resize(unsigned int size)
	{
		if(size > MaxSize)
		{
			return false;
		}
		m_size = size;
		return true;
	}

	inline _HOST_DEVICE_ bool clear() { return resize(0); }

	_HOST_DEVICE_ bool push_back(const T & element)
	{
		if(full())
		{
			return false;
		}
		m_elements[m_size++] = element;
		return true;
	}

	_HOST_DEVICE_ T pop_back()
	{
		if(empty())
		{
#ifndef _CUDACC_
			throw std::out_of_range("FixedSizeVector is empty.");
#else
			return T{};
#endif
		}
		return m_elements[m_size--];
	}

	// TODO: Range Check on access
	_HOST_DEVICE_ T & operator[](size_t i) { return m_elements[i]; }
	_HOST_DEVICE_ const T & operator[](size_t i) const { return m_elements[i]; }

	_HOST_DEVICE_ T * begin() { return &m_elements[0]; }
	_HOST_DEVICE_ T * end() { return &m_elements[m_size]; }

	_HOST_DEVICE_ const T * begin() const { return &m_elements[0]; }
	_HOST_DEVICE_ const T * end() const { return &m_elements[m_size]; }

private:
	T m_elements[MaxSize];
	unsigned int m_size;
};