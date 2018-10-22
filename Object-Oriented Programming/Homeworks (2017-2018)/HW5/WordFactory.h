#ifndef WORD_FACTORY_HDR
#define WORD_FACTORY_HDR

#include"Word.h"
#include"Date.h"
#include"Hashtag.h"
#include"Simple.h"

class WordFactory
{
public:
	WordFactory() = delete;
	WordFactory(const WordFactory&) = delete;
	WordFactory& operator=(const WordFactory&) = delete;
	~WordFactory() = delete;


	static Word* createWord(const char* str, const char* cmd);
};

#endif //WORD_FACTORY_HDR
