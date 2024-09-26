#pragma once

#include <utility>
#include <random>
#include <iostream>


class iterator;
class _reverse_iterator;


class Array
{
	public:

		using size_t = unsigned long long;
		using value_t = int;
		using range_t = std::pair<value_t, value_t>;

	public:

		Array(size_t size, range_t range) : m_size(size), m_data(new value_t[size]), m_capacity(size)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<value_t> rand_(range.first, range.second);

			for (size_t i = 0; i < size; ++i)
				m_data[i] = rand_(rng);
		}

		Array(const Array& arr) : m_data(new value_t[arr.m_size]), m_size(arr.m_size), m_capacity(arr.m_capacity)
		{
			*this = arr;
		}

		Array(size_t size) : m_data(new value_t[size]), m_size(0), m_capacity(size)
		{
		}

		~Array()
		{
			delete[] m_data;
		}

		Array& operator=(const Array& arr)
		{
			for (size_t i = 0; i < m_size; ++i)
				m_data[i] = arr[i];
			return *this;
		}

		void remove(size_t n)
		{
			if (n >= m_size) return;
			if (n != m_size - 1)
			{
				for (size_t i = n; i < m_size - 1; ++i)
					m_data[i] = m_data[i + 1];
			}
			--m_size;
		}

		void push(value_t elem)
		{
			if (m_size == m_capacity) return;
			m_data[m_size] = elem;
			++m_size;
		}

		void clear()
		{
			m_size = 0;
		}

		void print()
		{
			std::cout << "{";
			for (size_t i = 0; i < m_size; ++i)
				std::cout
				<< "[cell - "
				<< i + 1
				<< ",value - "
				<< m_data[i]
				<< "]"
				<< (i + 1 == m_size ? "" : ",");

			std::cout << "}" << std::endl;
		}

		void norm_print()
		{
			for (size_t i = 0; i < m_size; ++i)
				std::cout << m_data[i] << std::endl;
		}

		size_t size()
		{
			return m_size;
		}

		size_t capacity()
		{
			return m_capacity;
		}

		void swap(size_t lhs, size_t rhs)
		{
			value_t tmp = m_data[lhs];
			m_data[lhs] = m_data[rhs];
			m_data[rhs] = tmp;
		}

		value_t& operator[](size_t n)
		{
			return const_cast<value_t&>(static_cast<const Array&>(*this)[n]);
		}

		const value_t& operator[](size_t n) const
		{
			return m_data[n];
		}

	private:

		value_t* const m_data;
		size_t m_size, m_capacity;
};