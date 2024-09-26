#include "array.h"


#include <set>
unsigned long long check_for_lost_data(Array& data1, Array& data2)
{
	unsigned long long count = 0;

	std::multiset<Array::value_t> occurence, comp;

	for (Array::size_t i = 0; i < data1.size(); ++i)
		occurence.insert(data1[i]);

	for (Array::size_t i = 0; i < data2.size(); ++i)
		comp.insert(data2[i]);

	for (Array::size_t i = 0; i < data1.size(); ++i)
		if (occurence.count(data1[i]) != comp.count(data1[i]))
		{
			std::cout << "lost: " << data1[i] << std::endl;
			count += occurence.count(data1[i]) - comp.count(data1[i]);
		}

	std::cout << "TOTAL LOST: " << count << std::endl;

	return count;
}


#include <chrono>
void time_of(void (*func)(Array&, bool), Array& data, bool order)
{
	auto start = std::chrono::high_resolution_clock::now();
	func(data, order);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "TIME: " << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << " milliseconds" << std::endl;
}

void buble_sort(Array& data, bool order)
{
	auto algorithm = [&data](bool (*comp)(Array::value_t, Array::value_t))
		{
			for (Array::size_t i = 0; i < data.size(); ++i)
				for (Array::size_t ii = 1; ii < data.size(); ++ii)
				{
					if (comp(data[ii], data[ii - 1]))
						data.swap(ii, ii - 1);
				}
		};

	if (order)
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs < rhs; });
	}
	else
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs > rhs; });
	}
}


void insertion_sort(Array& data, bool order)
{
	auto algorithm = [&data](bool (*comp)(Array::value_t, Array::value_t))
		{
			for (Array::size_t i = 1; i < data.size(); ++i)
				for (Array::size_t ii = 0; ii < i; ++ii)
					if (comp(data[i], data[ii]))
					{
						Array::value_t tmp = data[i];
						for (Array::size_t iii = i; iii > ii; --iii)
							data[iii] = data[iii - 1];
						data[ii] = tmp;
					}
		};

	if (order)
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs < rhs; });
	}
	else
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs > rhs; });
	}
}


void selection_sort(Array& data, bool order)
{
	auto algorithm = [&data](bool (*comp)(Array::value_t, Array::value_t)) 
		{
			Array tmp(data);
			auto size = data.size();
			data.clear();
			for (Array::size_t i = 0; i < size; ++i)
			{
				Array::size_t index = 0;
				for (Array::size_t ii = 1; ii < tmp.size(); ++ii)
				{
					if (comp(tmp[ii], tmp[index]))
						index = ii;
				}
				data.push(tmp[index]);
				tmp.remove(index);
			}
		};

	if (order)
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs < rhs; });
	}
	else
	{
		algorithm([](Array::value_t lhs, Array::value_t rhs) {return lhs > rhs; });
	}
}


int main()
{
	Array arr(50, { -100, 100 }), arr_cp(arr);

	time_of(buble_sort, arr, 0);

	check_for_lost_data(arr, arr_cp);

	arr.norm_print();
}