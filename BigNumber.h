#pragma once
#include <vector>
#include <ostream>

class BigNumber
{
public:
	BigNumber();
	BigNumber(int32_t num);
	BigNumber(long long num);
	BigNumber operator~();
	BigNumber& operator^=(const BigNumber& big_number);
	BigNumber operator^(const BigNumber& big_number);
	BigNumber& operator&=(const BigNumber& big_number);
	BigNumber operator&(const BigNumber& big_number);
	BigNumber& operator|=(const BigNumber& big_number);
	BigNumber operator|(const BigNumber& big_number);
private:
	void bitwiseNOT();
	std::vector<uint32_t> number;
	bool sign = false;				// Знак, false - плюс, true - минус
};

