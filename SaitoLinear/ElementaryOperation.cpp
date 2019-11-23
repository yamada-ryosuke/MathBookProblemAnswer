#include "ElementaryOperation.hpp"
#include "Fraction.hpp"

using EO = ElementaryOperation<Fraction>;

EO elemOper;

int inputInteger();
Fraction inputFraction();
void output(const std::string& str);
void outputMatrix(const EO::Matrix& matrix);

void outputHelp();
void outputInvalid();
bool isValidIndex(const int index, const int size);

bool query(EO::Matrix& matrix);
void querySwitch(EO::Matrix& matrix, const bool is_row);
void queryMultiply(EO::Matrix& matrix, const bool is_row);
void queryAdd(EO::Matrix& matrix, const bool is_row);


int main()
{
	output("input matrix size.\n");
	output("row: ");
	const int row{inputInteger()};
	output("column: ");
	const int column{inputInteger()};
	if (row <= 0 || column <= 0)
	{
		output("too small.");
		return 0;
	}

	EO::Matrix matrix(row, EO::Row(column));

	output("input matrix like example.\n");
	output("example\n");
	output("1/2 5\n");
	output("3 10/3\n\n");
	for (auto& row: matrix)
		for (auto& elem: row)
			elem = inputFraction();
	output("\n");
	while (query(matrix));

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

void outputHelp()
{
	output("s [direction] [index1] [index2]\n");
	output("\t: switch [index1]th [direction] vector and [index2]th one\n");
	
	output("m [direction] [index] [multiplier]\n");
	output("\t: multiply [index]th [direction] vector by [multiplier]\n");

	output("m [direction] [from] [to] [multiplier]\n");
	output("\t: add [multiplier] times [from]th [direction] vector to [to]th one\n");

	output("[direction]: 'r' or 'c' that means row or column\n");

	output("exit: exit the program\n");
	output("output: output matrix\n");
	output("\n");
}

void outputInvalid()
{
	output("invalid\n");
	output("if you need help, input \"help\"\n");
}

bool isValidIndex(const int index, const int size)
{
	return 0 <= index && index < size;
}

bool query(EO::Matrix& matrix)
{
	output(">> ");
	std::string command;
	std::cin >> command;

	if (command == "exit")
		return false;
	else if (command == "help")
	{
		outputHelp();
		return true;
	}
	else if (command == "output")
	{
		outputMatrix(matrix);
		return true;
	}
	else if (command != "s" && command != "m" && command != "a")
	{
		outputInvalid();
		return true;
	}
	std::string direction;
	std::cin >> direction;
	if (direction != "r" && direction != "c")
	{
		outputInvalid();
		return true;
	}
	bool is_row{direction == "r"};
	if (command == "s")
		querySwitch(matrix, is_row);
	else if (command == "m")
		queryMultiply(matrix, is_row);
	else if (command == "a")
		queryAdd(matrix, is_row);
	outputMatrix(matrix);

	return true;
}

void querySwitch(EO::Matrix& matrix, const bool is_row)
{
	std::string index1Str, index2Str;
	std::cin >> index1Str >> index2Str;
	if (!std::all_of(index1Str.begin(), index1Str.end(), isdigit) || !std::all_of(index2Str.begin(), index2Str.end(), isdigit))
	{
		outputInvalid();
		return;
	}

	const int index1{std::stoi(index1Str)}, index2{std::stoi(index2Str)};
	const int size{is_row? (int)matrix.size(): (int)matrix.front().size()};
	if (!isValidIndex(index1, size) || !isValidIndex(index2, size))
	{
		outputInvalid();
		return;
	}
	if (is_row)
		elemOper.rowSwitch(matrix, index1, index2);
	else
		elemOper.columnSwitch(matrix, index1, index2);
}

void queryMultiply(EO::Matrix& matrix, const bool is_row)
{
	std::string indexStr;
	std::cin >> indexStr;
	const Fraction multiplier{inputFraction()};
	if (!std::all_of(indexStr.begin(), indexStr.end(), isdigit))
	{
		outputInvalid();
		return;
	}

	const int index{std::stoi(indexStr)};
	const int size{is_row? (int)matrix.size(): (int)matrix.front().size()};
	if (!isValidIndex(index, size))
	{
		outputInvalid();
		return;
	}
	if (is_row)
		elemOper.rowMultiply(matrix, index, multiplier);
	else
		elemOper.columnMultiply(matrix, index, multiplier);
}

void queryAdd(EO::Matrix& matrix, const bool is_row)
{
	std::string fromStr, toStr;
	std::cin >> fromStr >> toStr;
	const Fraction multiplier{inputFraction()};
	if (!std::all_of(fromStr.begin(), fromStr.end(), isdigit) || !std::all_of(toStr.begin(), toStr.end(), isdigit))
	{
		outputInvalid();
		return;
	}

	const int from{std::stoi(fromStr)}, to{std::stoi(toStr)};
	const int size{is_row? (int)matrix.size(): (int)matrix.front().size()};
	if (!isValidIndex(from, size) || !isValidIndex(to, size))
	{
		outputInvalid();
		return;
	}
	if (is_row)
		elemOper.rowAdd(matrix, from, to, multiplier);
	else
		elemOper.columnAdd(matrix, from, to, multiplier);
}