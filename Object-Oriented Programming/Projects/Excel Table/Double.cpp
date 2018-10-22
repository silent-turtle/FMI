#include "Double.h"



Double::Double(double num, size_t length) : num(num), num_length(length)
{
}

Double::~Double()
{
}

void Double::deserialise(std::ifstream & ifs)
{
	ifs >> num;
}

void Double::serialise(std::ofstream & ofs)
{
	ofs << num;
}
