#include "Simple.h"




Simple::Simple(const char* str) : content(nullptr)
{
	content_size = strlen(str);

	setContent(str);
}

Simple::~Simple()
{
	delete[] content;
}


size_t Simple::compareWords(const char* str)
{
	size_t size = strlen(str), idx = 0;
	double cnt = 0;

	while (str[idx] != '\0' && content[idx] != '\0')
	{
		if (*str == *content)
			++cnt;

		++idx;
	}

	if (str[idx] == '\0')
		return (cnt / size)* 100;

	if (content[idx] == '\0')
		return (cnt / content_size) * 100;
}

bool Simple::isSameLetter(char a, char b)
{
	if (a == b || a == b - ('a' - 'A') || a == b + ('a' - 'A'))
		return true;

	return false;
}

void Simple::setContent(const char* str)
{
	char* newMem = new char[content_size + 1];

	strncpy_s(newMem, content_size + 1, str, content_size);

	if (content) delete[] content;

	content = newMem;
}
