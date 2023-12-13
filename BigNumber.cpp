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

BigNumber& BigNumber::operator^=(const BigNumber& big_number)
{
	// Над числами a и b производится операция
	// побитового исключающего ИЛИ (XOR)
	// В результате этой операции число b изменяет число a
	
	auto& a_number = this->number;
	auto& b_number = big_number.number;

	auto a_length = a_number.size();
	auto b_length = b_number.size();
		
	if (a_length > b_length) {
		// Побитовое исключающее ИЛИ каждого
		// блока числа a и каждого блока числа b
		// до последнего блока b
		for (auto i = 0; i < b_length; ++i)
			a_number[i] ^= b_number[i];

		// Побитовое исключающее ИЛИ оставшихся
		// блоков числа a и нулевых блоков,
		// поскольку в числе b блоков не осталось
		for (auto i = b_length; i < a_length; ++i)
			a_number[i] ^= 0;
	}
	else if (b_length > a_length) {
		// Дополнение числа a нулевыми блоками
		a_number.resize(b_length, 0);

		// Побитовое исключающее ИЛИ каждого
		// блока числа a и каждого блока числа b
		for (auto i = 0; i < b_length; ++i)
			a_number[i] ^= b_number[i];
	}

	return *this;
}

BigNumber BigNumber::operator^(const BigNumber& big_number)
{
	BigNumber num = *this;
	num ^= big_number;
	return num;
}

BigNumber& BigNumber::operator&=(const BigNumber& big_number)
{
	// Над числами a и b производится
	// операция побитового И (AND)
	// В результате этой операции число b изменяет число a

	auto& a_number = this->number;
	auto& b_number = big_number.number;

	auto a_length = a_number.size();
	auto b_length = b_number.size();
	auto min_length = std::min(a_number.size(), b_number.size());

	// Число a не может быть по длине больше числа b,
	// поскольку в таком случае старшие блоки,
	// которые превзошли число b, зануляются
	if (a_length > b_length)
		a_number.resize(b_length);
	// Если число a будет по длине меньше числа b,
	// то это не приведет к проблемам, поскольку
	// мы даже не будем обращаться к тем блокам,
	// которые по длине превосходят число a

	// Побитовое И каждого
	// блока числа a и каждого блока числа b
	for (auto i = 0; i < min_length; ++i)
		a_number[i] &= b_number[i];

	return *this;
}

BigNumber BigNumber::operator&(const BigNumber& big_number)
{
	BigNumber num = *this;
	num &= big_number;
	return num;
}
