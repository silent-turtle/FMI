#ifndef WORD_HDR
#define WORD_HDR

#include<iostream>
#include<fstream>

class Word
{
public:
	Word() = default;
	Word(const Word&) = delete;
	Word& operator=(const Word&) = delete;
	virtual ~Word() { ; }

public:
	virtual const char* viewContent() const = 0;
	virtual size_t compareWords(const char* str) = 0;
};

#endif//WORD_HDR
