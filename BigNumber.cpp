#include "BigNumber.h"


BigNumber::BigNumber(long long num)
{
	// Получение старшего бита числа num
	// Если этот бит равен 1, то знак минус,
	// а если равен 0, то знак плюс
	sign = (num >> 63) & 1;

	// long long имеет размер 64 бита,
	// а каждый элемент вектора number имеет размер 32 бита,
	// поэтому необходимо 2 элемента вектора number
	number.resize(2);

	// Разбиваем num_copy на две части
	// Младшая часть пойдет в number[0]
	// Старшая часть пойдет в number[1]
	number[0] = num;
	number[1] = num >> 32;
}

void BigNumber::bitwiseNOT()
{
	for (auto& block : this->number)
		block = ~block;
}

BigNumber BigNumber::operator~()
{
	BigNumber num = *this;
	num.bitwiseNOT();
	return num;
}
