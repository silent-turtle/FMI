#ifndef USER_COLLECTION_HDR
#define USER_COLLECTION_HDR

#include"User.h"

class UserCollection
{
public:
	UserCollection();
	UserCollection(const UserCollection&) = delete;
	UserCollection& operator=(const UserCollection&) = delete;
	~UserCollection();

	void addUser(const char*, size_t);
	void addPostID(const char*, size_t);
	void removePostID(const char*, size_t);
	void print() const;
	void renameUser(const char*, size_t);
	void removeUser(size_t);

	void usersInfo();

	const User* getUser(size_t index) const { return users[index]; }
	const size_t getUsersSize() const { return users_size; }

private:
	User** users;
	size_t users_size;
	size_t users_capacity;
};

#endif //USER_COLLECTION_HDR
