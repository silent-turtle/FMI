#ifndef FMIBOOK_HDR
#define FMIBOOK_HDR

#include<iomanip>

#include"UserCollection.h"
#include"ModeratorCollection.h"
#include"Admin.h"
#include"PostCollection.h"
#include"BlockedUser.h"

class FMIBook
{
public:
	FMIBook(const char*, size_t);
	FMIBook(const FMIBook&) = delete;
	FMIBook& operator=(const FMIBook&) = delete;
	~FMIBook();

	void start();

private:
	void rename(const char* old_name, const char* new_name);
	
	void addUser(const char* actor, const char* name, size_t age);
	void removeUser(const char* actor, const char* name);
	
	void addMod(const char* actor, const char* name, size_t age);
	void removeModerator(const char* actor, const char* name);


	void addPost(const char* actor, const char* cmd, const char* text, const char* link = nullptr);
	void removePost(const char* actor, size_t id);
	
	void viewPost(size_t id);
	void viewUsersPosts(const char* name);

	void block(const char* actor, const char* name);
	void unblock(const char* actor, const char* name);

	void info();

	bool usernameExists(const char*);
	bool isModerator(const char*);
	bool isBlocked(const char*);

	const char* numToStr(size_t);	
	const char* getNicknameFromID(size_t id);

private:
	UserCollection users;
	ModeratorCollection mods;
	Admin admin;
	PostCollection posts;
	BlockedUser blocked;
};

#endif//FMIBOOK_HDR
