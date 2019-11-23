#pragma once
#include "Fraction.hpp"

class Elimination {
public:
	using T = Fraction;
	using Row = std::vector<T>;
	using Matrix = std::vector<Row>;

private:
	Matrix matrix_;
	int now_row{}, now_col{};

public:
	const int row, column;
	const Matrix &matrix;

	Elimination(const Matrix &initial)
		: matrix(initial), row((int)initial.size()), column((int)initial.front().size()) {}

	// // 掃き出しを進める。既に標準形になっていたらfalseを返す。
	// // 外部からはdo whileで回す。
	// bool next();
	
	// // 現在の行列の状況を表示する。
	// std::string view();
};