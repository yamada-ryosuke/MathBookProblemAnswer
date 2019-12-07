#include "Matrix.hpp"

int inputInteger();
Fraction inputFraction();
void output(const std::string& str);
void outputMatrix(const Matrix& matrix);

int main()
{
	output("input matrix size.\n");
	output("size: ");
	const int size{inputInteger()};
	if (size <= 0)
	{
		output("too small.\n");
		return 0;
	}

	Matrix matrix{size, size};

	output("input matrix like example.\n");
	output("example\n");
	output("1/2 5\n");
	output("3 10/3\n\n");
	for (auto& row: matrix)
		for (auto& elem: row)
			elem = inputFraction();
	output("\n");
	auto inverse{matrix.inverse()};
	if (inverse.first)
	{
		output("inverse:\n");
		inverse.second.output();
	}
	else
	{
		output("this matrix is not regular\n");
	}
	return 0;
}

int inputInteger()
{
	int num;
	std::cin >> num;
	return num;
}

Fraction inputFraction()
{
	std::string str;
	std::cin >> str;
	const int slash{(int)str.find_first_of('/')};
	const int64_t numer{std::stoi(str.substr(0, slash))};
	const int64_t denom{slash == std::string::npos? 1: std::stoi(str.substr(slash + 1))};
	return {numer, denom};
}

void output(const std::string& str)
{
	std::cout << str << std::flush;
}

void outputMatrix(const Matrix& matrix)
{
	const int m{matrix.M}, n{matrix.N};
	std::vector<std::string> lines(m);
	for (int col{}; col < n; col++)
	{
		int max_length{};
		for (int row{}; row < m; row++)
		{
			lines[row] += matrix[row][col].toString();
			max_length = std::max(max_length, (int)lines[row].size());
		}
		for (auto& line: lines)
			line.resize(max_length + 1, ' ');
	}
	for (auto& line: lines)
	{
		line.push_back('\n');
		output(line);
	}
}