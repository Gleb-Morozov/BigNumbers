#pragma once
#include <vector>

class BigNumbers
{
public:
	BigNumbers(long long num = 0);
private:
	std::vector<uint32_t> number;
	bool sign = false;				// ����, false - ����, true - �����
};

