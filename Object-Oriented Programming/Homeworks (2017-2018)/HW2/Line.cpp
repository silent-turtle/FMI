#include "Line.h"

Line::Line() : line(), words(nullptr), numOfWords(0)
{
}

Line::Line(Line& other) : numOfWords(other.numOfWords)
{
	seekLine(other.line);
	createWordsArr();
}

Line& Line::operator=(Line& other)
{
	if (this != &other)
	{
		numOfWords = other.numOfWords;
		seekLine(other.line);
		createWordsArr();
	}

	return *this;
}

Line::~Line()
{
	delete[] line;
	delete[] words;
}

void Line::createLine(char* str)
{
	seekLine(str);
	countWords();
	createWordsArr();
}

void Line::seekWordCount(size_t num)
{
	numOfWords = num;
}

size_t Line::getWordCount() const
{
	return numOfWords;
}

void Line::seekLine(const char* str)
{
	size_t size = strlen(str);

	char* newMem = new(std::nothrow) char[size + 1];
	if (!newMem)
	{
		std::cout << "Not enough memory!";
		return;
	}
	strncpy(newMem, str, size);
	newMem[size] = '\0';

	if(line)
	delete[] line;

	line = newMem;
}

void Line::countWords()
{
	const char* str = getLine();
	size_t size = strlen(str);
	size_t word_cnt = 1;

	for (size_t i = 0; i < size; ++i)
	{
		if (str[i] == ' ') ++word_cnt;
	}
	seekWordCount(word_cnt);
}

char* Line::getLine() const
{
	return line;
}

Word* Line::getWordArr() const
{
	return words;
}

void Line::createWordsArr()
{
	size_t i = 0;
	size_t word_cnt = 0;
	Word* newMem = new(std::nothrow) Word[numOfWords];
	if (!newMem)
	{
		std::cout << "Not enough memory!";
		return;
	}

	while (line[i] != '\0')
	{
		size_t pos = 0;
		char buffer[MAX_LINE_SIZE];
		while (line[i] != ' ')
		{
			if (!line[i]) break;
			buffer[pos] = line[i];
			++pos;
			++i;
		}
		if(line[i]) buffer[pos++] = line[i++];
		newMem[word_cnt].createWord(buffer, pos);

		++word_cnt;
	}

	delete[] words;
	words = newMem;
}