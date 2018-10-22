#include "Post.h"




Post::Post(const char* str, size_t num) : id(num), description(nullptr)
{
	setDescription(str);
}

Post::~Post()
{
	delete[] description;
}

//Post& Post::operator=(const Post& other)
//{
//	if (this != &other)
//	{
//		id = other.id;
//		setDescription(other.description);
//	}
//
//	return *this;
//}

void Post::setDescription(const char* str)
{
	size_t size = strlen(str);
	char* newMem;
	try
	{
		newMem = new char[size+1];
	}
	catch (std::bad_alloc&)
	{
		throw;
	}

	strncpy(newMem, str, size);
	newMem[size] = '\0';

	if (description) delete[] description;

	description = newMem;
}
