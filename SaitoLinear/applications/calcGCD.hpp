#pragma once
#include <bits/stdc++.h>

int64_t calcGCD(int64_t a, int64_t b)
{
	while (a)
	{
		b %= a;
		std::swap(a, b);
	}
	return b;
}