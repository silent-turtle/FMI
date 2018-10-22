#include "Date.h"



Date::Date(size_t d, size_t m, size_t y)
{
	const char* msg = "Invalid data!\n\n";

	if (m < 1 || m > 12)
		throw msg;

	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		if (d <= 0 || d >= 32) throw msg;

	if (m == 4 || m == 6 || m == 9 || m == 11)
		if (d <= 0 || d >= 31) throw msg;

	if (m == 2)
		if (y % 4 == 0)
		{
			if (y % 100 == 0)
			{
				if (y % 400 != 0)
					if (d > 28) throw msg;
					else
						if (d > 29) throw msg;
			}
			else
				if (d > 29) throw msg;
		}
		else
			if (d > 28) throw msg;


	day = d;
	month = m;
	year = y;
}


Date::~Date()
{ 
}

void Date::deserialise(std::ifstream & ifs)
{
	ifs >> day >> month >> year;
}

void Date::serialise(std::ofstream& ofs)
{
	ofs << day << '.' << month << '.' << year;
}

size_t Date::getLength() const
{
	size_t res = 6; //the number for days and months is always 2
	size_t temp = year;

	while (temp)
	{
		temp /= 10;
		++res;
	}

	return res;
}
