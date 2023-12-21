#include "BigNumber.h"


BigNumber::BigNumber()
{
}

BigNumber::BigNumber(int32_t num)
{
	// Если число num равно нулю,
	// то больше ничего менять не нужно:
	// - вектор number будет иметь нулевой размер
	// - переменная sign будет равна false
	if (num == 0)
		return;

	// Получение старшего бита числа num
	// Если этот бит равен 1, то знак минус,
	// а если равен 0, то знак плюс
	sign = (num >> 31) & 1;

	// Добавление в конец пустого вектора
	// number числа num
	number.push_back(num);
}

BigNumber::BigNumber(int64_t num)
{
	// Если число num равно нулю,
	// то больше ничего менять не нужно:
	// - вектор number будет иметь нулевой размер
	// - переменная sign будет равна false
	if (num == 0)
		return;
	
	uint32_t low_bits = num;		// Младшие 32 бита числа num
	uint32_t high_bits = num >> 32;	// Старшие 32 бита числа num
	
	// Если старшее число равно нулю,
	// то число положительное и
	// состоит только из одного блока
	if (high_bits == 0) {
		number.push_back(low_bits);
		sign = false;
	}
	else {
		// Получение старшего бита числа num
		// Если этот бит равен 1, то знак минус,
		// а если равен 0, то знак плюс
		sign = num & LLONG_MIN;

		// long long имеет размер 64 бита,
		// а каждый элемент вектора number имеет размер 32 бита,
		// поэтому необходимо 2 элемента вектора number
		number.resize(2);

		// Разбиваем num_copy на две части
		// Младшая часть пойдет в number[0]
		// Старшая часть пойдет в number[1]
		number[0] = low_bits;
		number[1] = high_bits;
	}
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
	auto min_length = std::min(a_length, b_length);

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

BigNumber& BigNumber::operator|=(const BigNumber& big_number)
{
	// Над числами a и b производится операция
	// побитового ИЛИ (OR)
	// В результате этой операции число b изменяет число a

	auto& a_number = this->number;
	auto& b_number = big_number.number;

	auto a_length = a_number.size();
	auto b_length = b_number.size();

	if (a_length > b_length) {
		// Побитовое ИЛИ каждого
		// блока числа a и каждого блока числа b
		// до последнего блока b
		for (auto i = 0; i < b_length; ++i)
			a_number[i] |= b_number[i];

		// Оставшиеся блоки числа a останутся без изменений,
		// поскольку в числе b не осталось блоков, 
		// т.е. оставшиеся блоки числа b равны нулю
	}
	else if (b_length > a_length) {
		// Дополнение числа a блоками до длины числа b
		a_number.resize(b_length);

		// Побитовое ИЛИ каждого ненулевого
		// блока числа a и каждого блока числа b
		for (auto i = 0; i < a_length; ++i)
			a_number[i] |= b_number[i];

		// Поскольку в числе a остались только новые нулевые блоки,
		// то можно скопировать оставшиеся блоки числа b
		// в нулевые блоки числа a
		for (auto i = a_length; i < b_length; ++i)
			a_number[i] = b_number[i];
	}

	return *this;
}

BigNumber BigNumber::operator|(const BigNumber& big_number)
{
	BigNumber num = *this;
	num |= big_number;
	return num;
}
