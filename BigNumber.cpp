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

BigNumber& BigNumber::operator^=(const BigNumber& big_number)
{
	// ��� ������� a � b ������������ ��������
	// ���������� ������������ ��� (XOR)
	// � ���������� ���� �������� ����� b �������� ����� a
	
	auto& a_number = this->number;
	auto& b_number = big_number.number;

	auto a_length = a_number.size();
	auto b_length = b_number.size();
		
	if (a_length > b_length) {
		// ��������� ����������� ��� �������
		// ����� ����� a � ������� ����� ����� b
		// �� ���������� ����� b
		for (auto i = 0; i < b_length; ++i)
			a_number[i] ^= b_number[i];

		// ��������� ����������� ��� ����������
		// ������ ����� a � ������� ������,
		// ��������� � ����� b ������ �� ��������
		for (auto i = b_length; i < a_length; ++i)
			a_number[i] ^= 0;
	}
	else if (b_length > a_length) {
		// ���������� ����� a �������� �������
		a_number.resize(b_length, 0);

		// ��������� ����������� ��� �������
		// ����� ����� a � ������� ����� ����� b
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
	// ��� ������� a � b ������������
	// �������� ���������� � (AND)
	// � ���������� ���� �������� ����� b �������� ����� a

	auto& a_number = this->number;
	auto& b_number = big_number.number;

	auto a_length = a_number.size();
	auto b_length = b_number.size();
	auto min_length = std::min(a_number.size(), b_number.size());

	// ����� a �� ����� ���� �� ����� ������ ����� b,
	// ��������� � ����� ������ ������� �����,
	// ������� ��������� ����� b, ����������
	if (a_length > b_length)
		a_number.resize(b_length);
	// ���� ����� a ����� �� ����� ������ ����� b,
	// �� ��� �� �������� � ���������, ���������
	// �� ���� �� ����� ���������� � ��� ������,
	// ������� �� ����� ����������� ����� a

	// ��������� � �������
	// ����� ����� a � ������� ����� ����� b
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
