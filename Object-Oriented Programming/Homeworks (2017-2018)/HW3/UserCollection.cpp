#include "UserCollection.h"



UserCollection::UserCollection() : users(nullptr), users_size(0), users_capacity(0)
{
}


UserCollection::~UserCollection()
{
	delete[] users;
}

void UserCollection::addUser(const char* name, size_t num)
{
	if (users_size >= users_capacity)
	{
		if (!users_size) users_capacity = 2;
		else users_capacity *= 2;

		User** newMem = new User*[users_capacity];

		for (size_t i = 0; i < users_size; ++i)
			newMem[i] = users[i];

		delete[] users;

		users = newMem;
	}
	users[users_size] = new User(name, num);
	++users_size;
}

void UserCollection::addPostID(const char* actor, size_t id)
{
	size_t size = getUsersSize();
	for (size_t i = 0; i < size; ++i)
		if (!strcmp(users[i]->getNickname(), actor))
			users[i]->addPostID(id);
}

void UserCollection::removePostID(const char* name, size_t id)
{
	for (size_t i = 0; i < users_size; ++i)
		if (!strcmp(users[i]->getNickname(), name))
		{
			users[i]->removePostID(id);
			return;
		}
}

void UserCollection::print() const
{
	for (size_t i = 0; i < users_size; ++i)
	{
		std::cout<< i+1 << " Name> " << users[i]->getNickname()
			<< "\nAge> " << users[i]->getAge() 
			<< "\nNumber of posts>" << users[i]->getPostIDsSize() << std::endl;
	}
}

void UserCollection::renameUser(const char* new_name, size_t index)
{
	users[index]->rename(new_name);
}

void UserCollection::removeUser(size_t index)
{
	if (users_size == 1)
	{
		delete users[0];
		users[0] = nullptr;
		--users_size;
		return;
	}
	User* temp = users[index];
	users[index] = users[users_size - 1];
	users[users_size - 1] = temp;

	delete temp;

	users[users_size - 1] = nullptr;

	--users_size;
}

void UserCollection::usersInfo()
{
	for (size_t i = 0; i < users_size; ++i)
		std::cout << users[i]->getNickname() << " - User, " 
		<< users[i]->getPostIDsSize() << " posts.\n";
}
