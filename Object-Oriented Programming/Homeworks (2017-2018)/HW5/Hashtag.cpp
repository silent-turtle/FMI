#include "Hashtag.h"



Hashtag::Hashtag(const char* str) : content(nullptr)
{
	if (str[0] != '#')
		throw "Invalid data!";

	content_size = strlen(str);

	setContent(str);
}


Hashtag::~Hashtag()
{
	delete[] content;
}

size_t Hashtag::compareWords(const char* str)
{
	if (!strcmp(str, viewContent())) 
		return 100;
	else 
		return 0;
}


void Hashtag::setContent(const char* str)
{
	char* newMem = new char[content_size + 1];

	strncpy_s(newMem, content_size + 1, str, content_size);

	if (content) delete[] content;

	content = newMem;
}