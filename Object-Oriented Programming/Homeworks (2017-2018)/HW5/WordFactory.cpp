#include "WordFactory.h"



//WordFactory::WordFactory()
//{
//}
//
//
//WordFactory::~WordFactory()
//{
//}

Word* WordFactory::createWord(const char* str, const char* cmd)
{
	if (!strcmp(cmd, "Simple"))
	{
		return new Simple(str);
	}
	if (!strcmp(cmd, "Hashtag"))
	{
		return new Hashtag(str);
	}
	if (!strcmp(cmd, "Date"))
	{
		return new Date(str);
	}

	return nullptr;
}
