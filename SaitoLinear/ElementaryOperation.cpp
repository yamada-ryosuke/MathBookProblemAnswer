#include "ElementaryOperation.hpp"
#include "Fraction.hpp"

using EO = ElementaryOperation<Fraction>;

int inputInteger();
Fraction inputFraction();
void output(const std::string& str);
void outputMatrix(const EO::Matrix& matrix);
bool query(EO::Matrix& matrix);

int main()
{
	output("input matrix size.\n");
	output("row: ");
	const int row{inputInteger()};
	output("column: ");
	const int column{inputInteger()};

	EO::Matrix matrix(row, EO::Row(column));

	output("input matrix like example.\n");
	output("example\n");
	output("1/2 5\n");
	output("3 10/3\n\n");
	for (auto& row: matrix)
		for (auto& elem: row)
			elem = inputFraction();
	output("\n");
	while (query());

	return 0;
}

void output(const std::string& str)
{
	std::cout << str << std::flush;
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

void outputMatrix(const EO::Matrix& matrix)
{
	const int height{(int)matrix.size()}, width{(int)matrix.front().size()};
	std::vector<std::string> lines(matrix.size());
	for (int col{}; col < width; col++)
	{
		int max_length{};
		for (int row{}; row < height; row++)
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

bool query(EO::Matrix matrix)
{
	output("input command. if you need help, input \"help\"");
	std::string command;
	std::cin >> command;

	if (command == "exit")
		return false;
	else if (command == "help")
	{
		output("input as \"[command] [direction] [option]\"\n");
		output("in command, input 's' or 'm' or 'a' that means switch or multiply or add\n");
		output("in direction, input 'r' or 'c' that means row or column\n");
		output("if command is s, option is [row1(column1)] [row2(column2)]\n");
		output("if command is m, option is [row(column)] [multiplier]\n");
		output("if command is a, option is [from] [to] [multiplier]\n");
		output("you should input \"exit\" to exit the program")

	}
	else if (command != "s" && command != "m" && command != "a")
		output("invalid input");

	// todo:機能実装
	return true;
}