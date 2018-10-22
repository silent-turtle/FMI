#ifndef WORD_HDR
#define WORD_HDR

#include<iostream>
#include<fstream>
#include<iomanip>

#include"Constants.h"

class Word
{
public:
	Word();
	Word(const Word&);
	Word& operator=(const Word&);
	~Word();

	void createWord(char* str, size_t num);
	char* getWord() const;
	size_t getSizeOfWord() const;


private:
	char* word;
	size_t sizeOfWord;
	
	void setWord(char* str);
	void setSizeOfWord(size_t num);
};

#endif //WORD_HDR
