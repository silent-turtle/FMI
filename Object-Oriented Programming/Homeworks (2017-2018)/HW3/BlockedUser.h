#ifndef BLOCKED_USER_HDR
#define BLOCKED_USER_HDR

#include<iostream>

class BlockedUser
{
public:
	BlockedUser();
	~BlockedUser();
	BlockedUser(const BlockedUser&) = delete;
	BlockedUser& operator=(const BlockedUser&) = delete;

	void addBlockedUser(const char*);
	void removeBlockedUser(const char*);

	void blockedInfo();

	const char* getBlockedUser(size_t index) const { return blocked_users[index]; }
	const size_t getBlockedUsersSize() const { return blocked_size; }

private:
	char** blocked_users;
	size_t blocked_size;
	size_t blocked_capacity;
};

#endif //BLOCKED_USER_HDR
