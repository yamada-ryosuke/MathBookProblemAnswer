#pragma once
#include <bits/stdc++.h>
#include "Fraction.hpp"

//////////
// 行列 //
//////////

// 加算、減算、乗算をもつM×N型行列
// M=Nで環をつくる
class Matrix {
public:
	using T = Fraction;
	using RowVector = std::vector<T>;

private:
	std::vector<RowVector> container_;

	// 必要に応じて書換
	const T ring_one{1, 1};
	const T ring_zero{0, 1};

public:
	const int M, N;

	Matrix(const int row_size, const int column_size)
		: M(row_size), N(column_size), container_(row_size, RowVector(column_size)){}
	// ムーブコンストラクタ
	Matrix(Matrix&& mat)
		: M(mat.M), N(mat.N), container_(std::move(mat.container_)){}
	// コピーコンストラクタ
	Matrix(const Matrix& mat)
		: M(mat.M), N(mat.N), container_(mat.container_){}

	// 要素アクセス
	RowVector& operator[](const int r) { return container_[r]; }
	const RowVector& operator[](const int r) const { return container_[r]; }
	// イテレータ
	typename decltype(container_)::iterator begin(){ return container_.begin(); }
	typename decltype(container_)::iterator end(){ return container_.end(); }

	// 環の演算
	Matrix operator+(const Matrix& mat) const
	{
		Matrix ret{*this};
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i][c_i] += mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix operator-(const Matrix& mat) const
	{
		Matrix ret{*this};
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i][c_i] -= mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix operator*(const Matrix& mat) const
	{
		Matrix ret(this->M, mat.N);
		for (int r_i{}; r_i < this->M; r_i++)
			for (int c_i{}; c_i < mat.N; c_i++)
				for (int l_i{}; l_i < this->N; l_i++)
					ret[r_i][c_i] += (*this)[r_i][l_i] * mat[l_i][c_i];
		return std::move(ret);
	}
	std::vector<T> operator*(const std::vector<T>& vec) const
	{
		std::vector<T> ret(M);
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i] += (*this)[r_i][c_i] * vec[c_i];
		return std::move(ret);
	}

	// 累乗
	Matrix operator^(const int64_t index) const
	{
		Matrix ret((*this).getOne()), pow(*this);
		for (int64_t i{index}; i > 0; i >>= 1)
		{
			if (i & 1)
				ret *= pow;
			pow *= pow;
		}
		return std::move(ret);
	}

	// 代入演算子
	Matrix& operator=(const Matrix& mat)
	{
		this->container_ = mat.container_;
		return *this;
	}	
	Matrix& operator+=(const Matrix& mat)
	{
		*this = *this + mat;
		return *this;
	}
	Matrix& operator-=(const Matrix& mat)
	{
		*this = *this - mat;
		return *this;
	}
	Matrix& operator*=(const Matrix& mat)
	{
		*this = *this * mat;
		return *this;
	}

	// ゼロ行列と単位行列
	Matrix getOne() const
	{
		Matrix ret(M, N);
		for (int i{}; i < N; i++)
			ret[i][i] = ring_one;
		return std::move(ret);
	}
	Matrix getZero() const
	{
		return Matrix(M, N);
	}

	// 逆行列
	std::pair<bool, Matrix> inverse()
	{
		if (M != N) return {false, {0, 0}};
		Matrix cpy{*this}, inv{getOne()};
		for (int row{}; row < M; row++)
		{
			for (int center{row}; center < M; center++)
				if (cpy[center][row] != Fraction{0, 1})
				{
					std::swap(cpy[center], cpy[row]);
					std::swap(inv[center], inv[row]);
					break;
				}
			if (cpy[row][row] == Fraction{0, 1})
				return {false, {0, 0}};
			
			{
				const Fraction ratio{cpy[row][row]};
				for (int col{N - 1}; col >= 0; col--)
				{
					inv[row][col] /= ratio;
					cpy[row][col] /= ratio;
				}
			}
			for (int minuend{}; minuend < M; minuend++)
			{
				if (minuend == row) continue;
				const Fraction ratio{cpy[minuend][row]};
				for (int col{}; col < N; col++)
				{
					cpy[minuend][col] -= ratio * cpy[row][col];
					inv[minuend][col] -= ratio * inv[row][col];
				}
			}
		}
		return {true, inv};
	}
};