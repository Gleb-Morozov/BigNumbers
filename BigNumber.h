#pragma once
#include <vector>
#include <ostream>

class BigNumber
{
public:
	BigNumber(long long num = 0);
	BigNumber operator~();
	BigNumber& operator^=(const BigNumber& big_number);
	BigNumber operator^(const BigNumber& big_number);
	BigNumber& operator&=(const BigNumber& big_number);
	BigNumber operator&(const BigNumber& big_number);
	BigNumber& operator|=(const BigNumber& big_number);
private:
	void bitwiseNOT();
	std::vector<uint32_t> number;
	bool sign = false;				// Знак, false - плюс, true - минус
};

