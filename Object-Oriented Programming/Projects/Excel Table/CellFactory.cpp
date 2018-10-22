#include "CellFactory.h"


Cell* CellFactory::createCell(const char* cmd, const char* content)
{
	if (!(strcmp(cmd, "Integer")))
	{
		int num = atoi(content);
		return new Integer(num);
	}

	if (!(strcmp(cmd, "Double")))
	{
		double num = atof(content);
		size_t size = strlen(content);
		return new Double(num, size);
	}

	if (!(strcmp(cmd, "Text")))
	{
		char* text = stringToText(content);
		//strncpy_s(text, size - 1, content + 1, size - 2);
		return new Text(text);
	}

	if (!(strcmp(cmd, "Date")))
	{
		size_t cnt = 0;
		int d, m, y;
		d = stringToInt(content, cnt, '.');
		m = stringToInt(content, cnt, '.');
		y = stringToInt(content, cnt);

		return new Date(d, m, y);
	}

	return nullptr;
}

int CellFactory::stringToInt(const char* str, size_t& cnt, char end)
{
	int res = 0;
	while (str[cnt] != end)
	{
		res *= 10;
		res += str[cnt] - '0';
		++cnt;
	}

	++cnt;
	return res;
}

char* CellFactory::stringToText(const char* str)
{
	char buffer[1024];
	size_t size = strlen(str);
	size_t b_cnt = 0;
	for (size_t s_cnt = 1; s_cnt < size - 1; ++s_cnt)
	{
		if (str[s_cnt] == '\\' && str[s_cnt + 1] == '\"');
		else 
		{
			buffer[b_cnt] = str[s_cnt];
			++b_cnt;
		}
	}

	char* newMem = new char[b_cnt + 1];

	strncpy_s(newMem, b_cnt + 1, buffer, b_cnt);

	return newMem;
}
