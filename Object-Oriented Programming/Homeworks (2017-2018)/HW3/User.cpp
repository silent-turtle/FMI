#include "User.h"



User::User(const char* name, size_t age) : nickname(nullptr), age(age), post_ids(nullptr), 
post_ids_size(0), post_ids_capacity(0)
{
	setNickname(name);
}

User::~User()
{
	delete[] nickname;
	delete[] post_ids;
}


void User::rename(const char* str)
{
	setNickname(str);
}

void User::addPostID(size_t id)
{
	if (post_ids_size >= post_ids_capacity)
	{
		if (!post_ids_size) post_ids_capacity = 2;
		else post_ids_capacity *= 2;

		size_t* newMem = new size_t[post_ids_capacity];

		for (size_t i = 0; i < post_ids_size; ++i)
			newMem[i] = post_ids[i];

		delete[] post_ids;

		post_ids = newMem;
	}

	post_ids[post_ids_size] = id;

	++post_ids_size;
}

void User::removePostID(size_t id)
{
	for (size_t i = 0; i < post_ids_size; ++i)
		if (post_ids[i] == id)
		{
			post_ids[i] = post_ids[post_ids_size - 1];
			--post_ids_size;
		}
}

void User::setNickname(const char* str)
{
	size_t size = strlen(str);

	char* newMem = new char[size + 1];
	strncpy(newMem, str, size);
	newMem[size] = '\0';

	if (nickname) delete[] nickname;

	nickname = newMem;
}

void User::setPostIDs(const size_t* arr)
{
	size_t* newMem = new size_t[post_ids_size];

	for (size_t i = 0; i < post_ids_size; ++i)
		newMem[i] = arr[i];

	if (post_ids) delete[] post_ids;

	post_ids = newMem;
}
