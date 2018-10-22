#ifndef USER_HDR
#define USER_HDR

#include<iostream>

class User
{
public:
	User(const char* name, size_t age_num);
	User(const User&) = delete;
	User& operator=(const User&) = delete;
	~User();

	void rename(const char*);
	void addPostID(size_t);
	void removePostID(size_t);
	const char* getNickname() const { return nickname; }
	const size_t getAge() const { return age; }
	const size_t getPostID(size_t index) const { return post_ids[index]; }
	const size_t getPostIDsSize() const { return post_ids_size; }

protected:
	char* nickname;
	size_t age;
	size_t* post_ids;
	size_t post_ids_size;
	size_t post_ids_capacity;

	void setNickname(const char*);
	void setPostIDs(const size_t*);
};

#endif //USER_HDR
