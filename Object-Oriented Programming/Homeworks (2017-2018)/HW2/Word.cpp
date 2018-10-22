#include "Word.h"

Word::Word() : word(nullptr), sizeOfWord(0)
{
}

Word::Word(const Word& other) : word(other.word)
{
	setWord(other.word);
}

Word& Word::operator=(const Word& other)
{
	if (this != &other)
	{
		sizeOfWord = other.sizeOfWord;

		setWord(other.word);
	}

	return *this;
}


Word::~Word()
{
	delete[] word;
}

void Word::createWord(char* str, size_t num)
{
	setSizeOfWord(num);
	setWord(str);
}

void Word::setWord(char* str)
{
	if (word)
	{
		delete[] word;
		word = nullptr;
	}
	
	word = new(std::nothrow) char[sizeOfWord + 1];
	if (!word)
	{
		std::cout << "Not enough memory!";
		return;
	}

	strncpy(word, str, sizeOfWord);

	word[sizeOfWord] = '\0';
}

void Word::setSizeOfWord(size_t num)
{
	sizeOfWord = num;
}

char * Word::getWord() const
{
	return word;
}

size_t Word::getSizeOfWord() const
{
	return sizeOfWord;
}
