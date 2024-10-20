#include <iostream>

#define print(x) std::cout << x << std::endl


void n1(int n, int out = 1)
{
	if (n < out)
		return;
	print(out << " ");
	return n1(n, out + 1);
}

void n2(int a, int b)
{
	if (a == b)
	{
		print(a << " ");
		return;
	}
	if (a < b)
	{
		print(a << " ");
		return n2(a + 1, b);
	}
	if (a > b)
	{
		print(a << " ");
		return n2(a - 1, b);
	}
}

void n3(int n)
{
	if (n == 2)
	{
		print("YES");
		return;
	}
	if (n < 2)
	{
		print("NO");
		return;
	}
	return n3(n / 2);
}

void n4v1(int n, int sum = 0) // using float arithmetic
{
	if (n == 0)
	{
		print(sum);
		return;
	}
	float f = float(n) / 10;
	return n4v1(n / 10, sum + ((f - int(f)) * 10));
}

#include <string>
void n4v2(int n, int sum = 0) // using string
{
	if (n == 0)
	{
		print(sum);
		return;
	}
	sum += std::to_string(n).back() - '0';
	return n4v2(n / 10, sum);
}

void n5v1(int n) // using float arithmetic
{
	if (n == 0)
		return;
	print(((float(n) / 10) - (n / 10)) * 10);
	return n5v1(n / 10);
}

void n5v2(int n) // using string
{
	if (n == 0)
		return;
	print(std::to_string(n).back());
	return n5v2(n / 10);
}

void n6(int n)
{
	auto s = std::to_string(n);
	print(s.front());
	s.erase(s.begin());
	if (n / 10 == 0)
		return;
	return n6(std::stoi(s));
}