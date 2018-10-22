#ifndef MODERATOR_HDR
#define MODERATOR_HDR

#include"User.h"


class Moderator : public User
{
public:
	Moderator(const char* name, size_t age_num);
	Moderator(const Moderator&) = delete;
	Moderator& operator=(const Moderator&) = delete;
	~Moderator();
};

#endif //MODERATOR_HDR
