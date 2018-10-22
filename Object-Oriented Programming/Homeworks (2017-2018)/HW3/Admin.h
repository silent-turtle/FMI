#ifndef ADMIN_HDR
#define ADMIN_HDR

#include"Moderator.h"
class Admin : public Moderator
{
public:
	Admin(const char*, size_t);
	Admin(const Admin&) = delete;
	Admin& operator=(const Admin&) = delete;
	~Admin();

	void adminInfo();
};

#endif //ADMIN_HDR
