#pragma once
#include <bits/stdc++.h>

template <typename T>
class ElementaryOperation {
public:
	using Row = std::vector<T>;
	using Matrix = std::vector<Row>;

	void rowSwitch(Matrix& matrix, const int row1, const int row2);
	void rowMultiply(Matrix& matrix, const int row, const T multi);
	void rowAdd(Matrix& matrix, const int from, const int to, const T multi);

	void columnSwitch(Matrix& matrix, const int col1, const int col2);
	void columnMultiply(Matrix& matrix, const int col, const T multi);
	void columnAdd(Matrix& matrix, const int from, const int to, const T multi);
};

template <typename T>
void ElementaryOperation<T>::rowSwitch(Matrix& matrix, const int row1, const int row2)
{
	std::swap(matrix[row1], matrix[row2]);
}

template <typename T>
void ElementaryOperation<T>::rowMultiply(Matrix& matrix, const int row, const T multi)
{
	for (auto& e: matrix[row])
		e *= multi;
}

template <typename T>
void ElementaryOperation<T>::rowAdd(Matrix& matrix, const int from, const int to, const T multi)
{
	for (int col{}; col < matrix[from].size(); col++)
		matrix[to][col] += matrix[from][col] * multi;
}

template <typename T>
void ElementaryOperation<T>::columnSwitch(Matrix& matrix, const int col1, const int col2)
{
	for (auto& row: matrix)
		std::swap(row[col1], row[col2]);
}

template <typename T>
void ElementaryOperation<T>::columnMultiply(Matrix& matrix, const int col, const T multi)
{
	for (auto& row: matrix)
		row[col] *= multi;
}

template <typename T>
void ElementaryOperation<T>::columnAdd(Matrix& matrix, const int from, const int to, const T multi)
{
	for (auto& row: matrix)
		row[to] += row[from] * multi;
}