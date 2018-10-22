#include "Date.h"



Date::Date(const char* str) : content(nullptr)
{
	content_size = strlen(str);

	setContent(str);

	setDate();
}

Date::~Date()
{
	delete[] content;
}

size_t Date::compareWords(const char* str)
{
	size_t cnt = 0;
	size_t other_day = strToInt(str, cnt, '-');
	size_t other_month = strToInt(str, cnt, '-');
	size_t other_year = strToInt(str, cnt, '\0');

	if (day == other_day && month == other_month && year == other_year) return 100;

	size_t res = 0;
	size_t res1 = dateToDayOfYear(day, month);
	size_t res2 = dateToDayOfYear(other_day, other_month);

	if (isLeapYear(year))
		++res1;

	if (isLeapYear(other_year))
		++res2;

	if (year == other_year)
	{
		if (res1 > res2)
			res = res1 - res2;
		else
			res = res2 - res1;
	}
	else
		if (year > other_year)
		{
			res1 += (year - other_year) * 365;
			res = res1 - res2;
		}
		else
		{
			res2 += (other_year - year) * 365;
			res = res2 - res1;
		}

	if (res < 100)
		return 100 - res;
	else return 0;
}

void Date::setContent(const char* str)
{
	char* newMem = new char[content_size + 1];

	strncpy_s(newMem, content_size + 1, str, content_size);

	if (content) delete[] content;

	content = newMem;
}

void Date::setDate()
{
	size_t cnt = 0;
	day = strToInt(content, cnt, '-');
	month = strToInt(content, cnt, '-');
	year = strToInt(content, cnt, '\0');

	if (!isValidDate()) throw "Invalid data!\n\n";
}

size_t Date::strToInt(const char* str, size_t& cnt, char end)
{
	size_t res = 0;
	while (str[cnt] != end)
	{
		res *= 10;
		res += str[cnt] - '0';
		++cnt;
	}

	++cnt;
	return res;
}

bool Date::isLeapYear(size_t year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 != 0)
				return true;
			else return false;
		}
		else return true;
	}
	else return false;
}

bool Date::isValidDate()
{
	if (month > 12)
		return false;

	if (month == 1 || month == 3 || month == 5 || month == 7 || 
		month == 8 || month == 10 || month == 12)
		if (day > 31) return false;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day > 30) return false;

	if (month == 2)
	{
		if (isLeapYear(year))
		{
			if (day > 29) return false;
		}
		else
			if (day > 28) return false;
	}

	return true;
}

size_t Date::dateToDayOfYear(size_t d, size_t m)
{
	if (m == 1)
		return d;

	if (m == 2)
		return d + 31;

	size_t monthsWith30Days = (m - 1) / 2 - 1;
	size_t monthsWith31Days = (m - 1) - monthsWith30Days - 1;

	if (m == 9 || m == 11)
	{
		--monthsWith30Days;
		++monthsWith31Days;
	}

	size_t res = 28;

	res += (monthsWith30Days * 30);
	res += (monthsWith31Days * 31);
	res += d;

	return res;
}
