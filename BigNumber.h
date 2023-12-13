#pragma once
#include <vector>
#include <ostream>

class BigNumber
{
public:
	BigNumber(long long num = 0);
	BigNumber operator~();
private:
	void bitwiseNOT();
	std::vector<uint32_t> number;
	bool sign = false;				// ����, false - ����, true - �����
};

