#include "BigNumber.h"


BigNumber::BigNumber(long long num)
{
	// ��������� �������� ���� ����� num
	// ���� ���� ��� ����� 1, �� ���� �����,
	// � ���� ����� 0, �� ���� ����
	sign = (num >> 63) & 1;

	// long long ����� ������ 64 ����,
	// � ������ ������� ������� number ����� ������ 32 ����,
	// ������� ���������� 2 �������� ������� number
	number.resize(2);

	// ��������� num_copy �� ��� �����
	// ������� ����� ������ � number[0]
	// ������� ����� ������ � number[1]
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
