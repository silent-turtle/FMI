#ifndef LINE_HDR
#define LINE_HDR

#include"Word.h"

#include<iostream>
#include<fstream>

class Line
{
public:
	Line();
	Line(Line&);
	Line & operator=(Line&);
	~Line();

	void createLine(char* str);
	
	size_t getWordCount() const;
	char* getLine() const;
	Word* getWordArr() const;

private:
	char* line;
	Word* words;
	size_t numOfWords;

	void createWordsArr();
	void seekWordCount(size_t num);
	void seekLine(const char* str);
	void countWords();
};

#endif //LINE_HDR
