#include "BlockedUser.h"



BlockedUser::BlockedUser() : blocked_users(nullptr), blocked_size(0), blocked_capacity(0)
{
}


BlockedUser::~BlockedUser()
{
	delete[] blocked_users;
}

void BlockedUser::addBlockedUser(const char* name)
{
	if (blocked_size >= blocked_capacity)
	{
		if (blocked_size == 0) blocked_capacity = 2;
		else blocked_capacity *= 2;

		char** newMem = new char*[blocked_capacity];

		for (size_t i = 0; i < blocked_size; ++i)
			newMem[i] = blocked_users[i];

		delete[] blocked_users;

		blocked_users = newMem;
	}

	size_t size = strlen(name);

	blocked_users[blocked_size] = new char[size + 1];
	strncpy(blocked_users[blocked_size], name, size);
	blocked_users[blocked_size][size] = '\0';

	++blocked_size;

	std::cout << name << " blocked.\n";
}

void BlockedUser::removeBlockedUser(const char* name)
{
	if (blocked_size == 1)
	{
		delete[] blocked_users[0];
		blocked_users[0] = nullptr;
		--blocked_size;
		return;
	}

	for (size_t i = 0; i < blocked_size; ++i)
	{
		if (!strcmp(blocked_users[i], name))
		{
			char* temp = blocked_users[i];
			blocked_users[i] = blocked_users[blocked_size - 1];
			blocked_users[blocked_size - 1] = temp;

			delete[] blocked_users[blocked_size - 1];
			blocked_users[blocked_size - 1] = nullptr;

			--blocked_size;

			std::cout << name << " unblocked.\n";

			return;
		}
	}
}

void BlockedUser::blockedInfo()
{
	std::cout << "Blocked users: " << blocked_size << ".\n";

	for (size_t i = 0; i < blocked_size; ++i)
	{
		std::cout << getBlockedUser(i);
		if (i != blocked_size - 1) std::cout << ",\n";
	}
	std::cout << ".\n";
}
