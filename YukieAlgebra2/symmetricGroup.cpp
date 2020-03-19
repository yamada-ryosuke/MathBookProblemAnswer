#include <iostream>
#include <string>
#include <vector>
#include <numeric>

std::vector<std::vector<int>> initGroup();

int main()
{
	const std::vector<std::vector<int>> group(initGroup());
	const int order{(int)group.size()}, set_size{(int)group.front().size()};;
	for (int i{}; i < order; i++)
	{
		std::cout << i + 1 << ":";
		for (auto& e: group[i])
			std::cout << ' ' << e + 1;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\\r";
	for (int i{}; i < order; i++)
		std::cout << ' ' << i + 1;
	std::cout << std::endl << "l\\" << std::endl;
	for (int left_i{}; left_i < order; left_i++)
	{
		std::cout << left_i + 1 << ' ';
		const auto& left{group[left_i]};
		for (auto& right: group)
		{
			std::vector<int> multiple(set_size);
			for (int i{}; i < set_size; i++)
				multiple[i] = left[right[i]];
			for (int i{}; i < order; i++)
				if (multiple == group[i])
				{
					std::cout << ' ' << i + 1;
					break;
				}
		}
		std::cout << std::endl;
	}

	return 0;
}

std::vector<std::vector<int>> initGroup()
{
	const int cardinal{3};
	std::vector<std::vector<int>> cyclic
	{
		{},
		{1, 2},
		{1, 3},
		{2, 3},
		{1, 2, 3},
		{1, 3, 2}
	};

	std::vector<std::vector<int>> ret(cyclic.size(), std::vector<int>(cardinal));
	for (auto& e: ret)
		std::iota(e.begin(), e.end(), 0);
	for (int i{}; i < (int)cyclic.size(); i++)
		for (int j{}; j < (int)cyclic[i].size() - 1; j++)
			std::swap(ret[i][cyclic[i][j] - 1], ret[i][cyclic[i][j + 1] - 1]);

	return ret;
}