#pragma once
#include <vector>
#include <ostream>

class BigNumber
{
public:
	BigNumber(long long num = 0);
private:
	std::vector<uint32_t> number;
	bool sign = false;				// Знак, false - плюс, true - минус
};

