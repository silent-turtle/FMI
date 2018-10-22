#include "Integer.h"



Integer::Integer(int num) : num(num)
{
}


Integer::~Integer()
{
}

void Integer::deserialise(std::ifstream& ifs)
{
	ifs >> num;
}

void Integer::serialise(std::ofstream& ofs)
{
	ofs << num;
}

size_t Integer::getLength() const
{
	size_t res = 0;
	int temp = num;
	//if (temp < 0) temp = -temp;
	while (temp)
	{
		temp /= 10;
		++res;
	}

	return res;
}
