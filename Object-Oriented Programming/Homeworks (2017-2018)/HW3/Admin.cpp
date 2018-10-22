#include "Admin.h"



Admin::Admin(const char* str, size_t num) : Moderator(str, num)
{
}


Admin::~Admin()
{
}

void Admin::adminInfo()
{
	std::cout << getNickname() << " - Administrator, " << getPostIDsSize() << " posts.\n";

}
