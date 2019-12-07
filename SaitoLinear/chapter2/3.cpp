#include "../Matrix.hpp"

int main()
{
	const Matrix A{
		{
			{-1, -5, -1},
			{ 2,  4,  0},
			{-4, -8,  0}
		}
	};
	const Matrix P{
		{
			{ 1,  3,  2},
			{-1, -2, -1},
			{ 2,  4,  3}
		}
	};
	
	auto inverse{P.inverse().second};
	std::cout << "inverse:" << std::endl;
	inverse.output();
	std::cout << "P^-1 A P:" << std::endl;
	(inverse * A * P).output();
	const Matrix coefficient2{
		{
			{1, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		}
	};
	const Matrix coefficient1{
		{
			{0, 0, 0},
			{0, 1, 0},
			{0, 0, 0}
		}
	};
	std::cout << "coefficient of 2^n:" << std::endl;
	(P * coefficient2 * inverse).output();
	std::cout << "coefficient of 1:" << std::endl;
	(P * coefficient1 * inverse).output();

	return 0;
}