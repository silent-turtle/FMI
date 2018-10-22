#include "Text.h"



Text::Text() : text(nullptr)
{
}


Text::Text(const char* str)
{
	text_size = strlen(str);
	setText(str);
}

Text::~Text()
{
	delete[] text;
}

void Text::deserialise(std::ifstream& ifs)
{
	char buffer[128];
	ifs.getline(buffer, 128);

	setText(buffer);
}

void Text::serialise(std::ofstream& ofs)
{
	ofs << "\"" << text << "\"";
}


void Text::setText(const char* str)
{
	char* newMem = new char[text_size + 1];

	strncpy_s(newMem, text_size + 1, str, text_size);

	if (text) delete[] text;

	text = newMem;
}