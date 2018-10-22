#include "FMIBook.h"

const size_t MAX_ACTOR_SIZE = 256;
const size_t MAX_ACTION_SIZE = 16;
const size_t MAX_SUBJECT_SIZE = 256;
const size_t MAX_POST_TYPE_SIZE = 10;
const size_t MAX_LINK_SIZE = 256;
const size_t SIZE_OF_STR_POST = 4;
const size_t SIZE_OF_STR_HTML = 5;

FMIBook::FMIBook(const char* str, size_t num) : admin(str, num)
{
}

FMIBook::~FMIBook()
{
}

void FMIBook::start()
{
	char actor[MAX_ACTOR_SIZE];
	char subject[MAX_SUBJECT_SIZE];
	char action[MAX_ACTION_SIZE];

	do
	{
		std::cin >> std::setw(MAX_ACTOR_SIZE) >> actor;

		if (!strcmp("info", actor))
		{
			info();
			continue;
		}
		if (!strcmp("quit", actor))
			continue;

		std::cin >> std::setw(MAX_ACTION_SIZE) >> action;
		if (!strcmp("add_user", action))
		{
			size_t age;
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;
			std::cin >> age;

			try 
			{
			addUser(actor, subject, age);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't add a new user. Not enough memory!\n\n";
			}
		}
		else if (!strcmp("add_moderator", action))
		{
			size_t age;
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;
			std::cin >> age;

			try
			{
				addMod(actor, subject, age);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't add a new moderator. Not enough memory!\n\n";
			}
		}
		else if (!strcmp("rename", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;

			try
			{
				rename(actor, subject);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't rename the user. Not enough memory!\n\n";
			}
		}
		else if (!strcmp("remove_user", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;

			removeUser(actor, subject);
		}
		else if (!strcmp("remove_moderator", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;
			removeUser(actor, subject);
		}
		else if (!strcmp("block", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;

			try 
			{
			block(actor, subject);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Not enough memory!\n\n";
			}
		}
		else if (!strcmp("unblock", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;
			unblock(actor, subject);
		}
		else if (!strcmp("post", action))
		{
			char post_type[MAX_POST_TYPE_SIZE];
			char link[MAX_LINK_SIZE];

			std::cin >> std::setw(MAX_POST_TYPE_SIZE) >> post_type;
			std::cin.getline(subject, MAX_SUBJECT_SIZE);

			if (!strcmp("[url]", post_type))
				std::cin >> std::setw(MAX_LINK_SIZE) >> link;
			try
			{
			addPost(actor, post_type, subject, link);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't add a new post. Not enough memory!\n\n";
			}
		}
		else if (!strcmp("remove_post", action))
		{
			size_t post_id;
			std::cin >> post_id;

			removePost(actor, post_id);
		}
		else if (!strcmp("view_post", action))
		{
			size_t post_id;
			std::cin >> post_id;
			try 
			{
			viewPost(post_id);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't create an HTML file for the post. Not enough memory!\n\n";
			}
		}
		else if (!strcmp("view_all_posts", action))
		{
			std::cin >> std::setw(MAX_SUBJECT_SIZE) >> subject;

			try 
			{
			viewUsersPosts(subject);
			}
			catch (std::bad_alloc&)
			{
				std::cout << "Couldn't create an HTML file for the user's posts. Not enough memory!\n\n";
			}
		}
		else
		{
			std::cout << "Unknown command!\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (strcmp("quit", actor));
}

void FMIBook::rename(const char* old_name, const char* new_name)
{
	if (usernameExists(new_name))
	{
		std::cout << new_name << " already exists!\n\n";
		return;
	}

	size_t users_size = users.getUsersSize();
	size_t mods_size = mods.getModeratorsSize();
	for (size_t i = 0; i < users_size; ++i)
	{
		if (!strcmp(users.getUser(i)->getNickname(), old_name))
		{
			users.renameUser(new_name, i);
			std::cout << "User " << old_name << " is now known as " << new_name << ".\n\n";
			return;
		}
	}

	for (size_t i = 0; i < mods_size; ++i)
	{
		if (!strcmp(mods.getModerator(i)->getNickname(), old_name))
		{
			mods.renameModerator(new_name, i);
			std::cout << "User " << old_name << " is now known as " << new_name << ".\n\n";
			return;
		}
	}

	if (!strcmp(admin.getNickname(), old_name))
		admin.rename(new_name);
}

void FMIBook::addUser(const char* actor, const char* name, size_t num)
{
	if (strcmp(actor, admin.getNickname()))
	{
		std::cout << "The user cannot do that!\n\n";
		return;
	}

	if (usernameExists(name))
	{
		std::cout << name << " already exists!\n\n";
		return;
	}

	users.addUser(name, num);
	std::cout << name << " created.\n\n";
}

void FMIBook::addMod(const char* actor, const char* name, size_t num)
{
	if (strcmp(actor, admin.getNickname()))
	{
		std::cout << actor << " cannot do that!\n\n";
		return;
	}

	if (usernameExists(name))
	{
		std::cout << name << " already exists!\n\n";
		return;
	}

	mods.addModerator(name, num);
	std::cout << name << " created.\n\n";
}

void FMIBook::removeUser(const char* actor, const char* name)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	if (strcmp(admin.getNickname(), actor))
	{
		std::cout << actor << " cannot do that!\n\n";
		return;
	}

	if (!strcmp(admin.getNickname(), name))
	{
		std::cout << "Admin cannot remove themselves!\n\n";
		return;
	}

	size_t user_size = users.getUsersSize();

	for (size_t i = 0; i < user_size; ++i)
	{
		if (!strcmp(users.getUser(i)->getNickname(), name))
		{
			size_t post_size = users.getUser(i)->getPostIDsSize();
			for (size_t j = 0; j < post_size; ++j)
			{
				size_t id = users.getUser(i)->getPostID(j);
				removePost(actor, id);
			}
			users.removeUser(i);
			std::cout << name << " removed.\n\n";
			break;
		}
	}
}

void FMIBook::removeModerator(const char* actor, const char* name)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	if (strcmp(admin.getNickname(), actor))
	{
		std::cout << actor << " cannot do that!\n\n";
		return;
	}

	if (!strcmp(admin.getNickname(), name))
	{
		std::cout << "Admin cannot remove themselves!\n\n";
		return;
	}

	size_t mod_size = mods.getModeratorsSize();

	for (size_t i = 0; i < mod_size; ++i)
	{
		if (!strcmp(mods.getModerator(i)->getNickname(), name))
		{
			size_t post_size = mods.getModerator(i)->getPostIDsSize();
			for (size_t j = 0; j < post_size; ++j)
			{
				size_t id = mods.getModerator(i)->getPostID(j);
				removePost(actor, id);
			}
			mods.removeModerator(i);
			std::cout << name << " removed.\n\n";
			break;
		}
	}
}

void FMIBook::addPost(const char* actor, const char* type, const char* text, const char* link)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	if (isBlocked(actor))
	{
		std::cout << "Post not created - user is blocked!\n\n";
		return;
	}

	posts.addPost(type, text, link);

	size_t size = posts.getPostSize();
	size_t post_id = posts.getPost(size)->getID();

	users.addPostID(actor, post_id);
	mods.addPostID(actor, post_id);
	admin.addPostID(post_id);
	std::cout << "Post " << post_id << " created.\n\n";
}

void FMIBook::viewPost(size_t id)
{
	if (!posts.postExists(id))
	{
		std::cout << "There's no such post!\n\n";
		return;
	}

	const char* path = numToStr(id);

	std::ofstream ofs;
	ofs.open(path);

	if (!ofs.is_open())
	{
		std::cout << "Cannot open file!\n\n";
		return;
	}

	posts.createHTMLFile(id, ofs);

	ofs.close();

	std::cout << "HTML view for post " << id << " created.\n\n";
}

void FMIBook::viewUsersPosts(const char* name)
{
	if (!usernameExists(name))
	{
		std::cout << name << " doesn't exist!'\n\n";
		return;
	}

	size_t user_size = users.getUsersSize();
	size_t mod_size = mods.getModeratorsSize();

	size_t name_size = strlen(name);
	const char* temp = "'sPosts.html";
	size_t temp_size = strlen(temp);
	char* path = new char[name_size + temp_size + 1];

	strncpy(path, name, name_size);
	strncpy(path + name_size, temp, temp_size);
	path[name_size + temp_size] = '\0';


	std::ofstream ofs;
	ofs.open(path);

	if (!ofs.is_open())
	{
		std::cout << "Cannot open file!\n\n";
		return;
	}

	for (size_t i = 0; i < user_size; ++i)
	{
		const User* temp = users.getUser(i);
		if (!strcmp(name, temp->getNickname()))
		{
			size_t post_size = temp->getPostIDsSize();
			for (size_t j = 0; j < post_size; ++j)
			{
				size_t id = temp->getPostID(j);
				posts.createHTMLFile(id, ofs);
				ofs << "<br/>";
			}
			ofs.close();
			return;
		}
	}

	for (size_t i = 0; i < mod_size; ++i)
	{
		const Moderator* temp = mods.getModerator(i);
		if (!strcmp(name, temp->getNickname()))
		{
			size_t post_size = temp->getPostIDsSize();
			for (size_t j = 0; j < post_size; ++j)
			{
				size_t id = temp->getPostID(j);
				posts.createHTMLFile(id, ofs);
				ofs << "<br/>";
			}
			ofs.close();
			return;
		}
	}

	if (!strcmp(name, admin.getNickname()))
	{
		size_t post_size = admin.getPostIDsSize();
		for (size_t i = 0; i < post_size; ++i)
		{
			size_t id = admin.getPostID(i);
			posts.createHTMLFile(id, ofs);
			ofs << "<br/>";
		}
		ofs.close();
	}

	std::cout << "HTML view for all " << name << "'s posts created.\n\n";
}

void FMIBook::removePost(const char* actor, size_t id)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	const char* name = getNicknameFromID(id);

	if (name == nullptr)
	{
		std::cout << "There's no such post!\n\n";
		return;
	}

	if (strcmp(admin.getNickname(), actor)) //if the actor is a user trying to delete another user's post
		if (!isModerator(actor))
			if (strcmp(actor, name))
			{
				std::cout << actor << " doesn't have the rights to remove other posts!\n\n";
				return;
			}

	posts.removePost(id);
	users.removePostID(name, id);
	mods.removePostID(name, id);

	std::cout << "Post " << id << " removed.\n\n";
}

void FMIBook::block(const char* actor, const char* name)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	if (!strcmp(actor, name))
	{
		std::cout << actor << " cannot block themselves!\n\n";
		return;
	}

	if (!usernameExists(name))
	{
		std::cout << name << " doesn't exist!\n\n";
		return;
	}

	if (!isModerator(actor))
		if (strcmp(admin.getNickname(), actor))
		{
			std::cout << actor << " doesn't have the rights to block users!\n\n";
			return;
		}

	if (isBlocked(name))
	{
		std::cout << name << " is already blocked!\n\n";
		return;
	}


	blocked.addBlockedUser(name);

	std::cout << name << " blocked.\n\n";
}

void FMIBook::unblock(const char* actor, const char* name)
{
	if (!usernameExists(actor))
	{
		std::cout << actor << " doesn't exist!\n\n";
		return;
	}

	if (!usernameExists(name))
	{
		std::cout << name << " doesn't exist!\n\n";
		return;
	}

	if (!isModerator(actor) || strcmp(admin.getNickname(), actor))
	{
		std::cout << actor << " doesn't have the rights to unblock users!\n\n";
		return;
	}

	if (!strcmp(actor, name))
	{
		std::cout << actor << " cannot unblock themselves!\n\n";
		return;
	}

	blocked.removeBlockedUser(name);
	std::cout << name << " unblocked.\n\n";
}

void FMIBook::info()
{
	size_t blocked_size = blocked.getBlockedUsersSize();
	size_t mod_size = mods.getModeratorsSize();
	size_t user_size = users.getUsersSize();

	size_t total_users_size = user_size + mod_size + 1;

	std::cout << "Total users: " << total_users_size << std::endl;

	admin.adminInfo();
	mods.moderatorsInfo();
	users.usersInfo();
	blocked.blockedInfo();

	size_t min_age = admin.getAge();

	for (size_t i = 0; i < user_size; ++i)
	{
		size_t temp = users.getUser(i)->getAge();
		if (min_age > temp) min_age = temp;
	}

	for (size_t i = 0; i < mod_size; ++i)
	{
		size_t temp = mods.getModerator(i)->getAge();
		if (min_age > temp) min_age = temp;
	}

	std::cout << "Youngest: ";

	for (size_t i = 0; i < user_size; ++i)
		if (users.getUser(i)->getAge() == min_age)
			std::cout << users.getUser(i)->getNickname() << ' ' << min_age << std::endl;

	for (size_t i = 0; i < mod_size; ++i)
		if (mods.getModerator(i)->getAge() == min_age)
			std::cout << mods.getModerator(i)->getNickname() << ' ' << min_age << std::endl;

	if (admin.getAge() == min_age)
		std::cout << admin.getNickname() << ' ' << min_age << std::endl;

	size_t max_age = admin.getAge();

	for (size_t i = 0; i < user_size; ++i)
	{
		size_t temp = users.getUser(i)->getAge();
		if (max_age < temp) max_age = temp;
	}

	for (size_t i = 0; i < mod_size; ++i)
	{
		size_t temp = mods.getModerator(i)->getAge();
		if (max_age < temp) max_age = temp;
	}

	if (max_age < admin.getAge()) max_age = admin.getAge();

	std::cout << "Oldest: ";

	for (size_t i = 0; i < user_size; ++i)
		if (users.getUser(i)->getAge() == max_age)
			std::cout << users.getUser(i)->getNickname() << ' ' << max_age << std::endl << std::endl;

	for (size_t i = 0; i < mod_size; ++i)
		if (mods.getModerator(i)->getAge() == max_age)
			std::cout << mods.getModerator(i)->getNickname() << ' ' << max_age << std::endl << std::endl;

	if (admin.getAge() == max_age)
		std::cout << admin.getNickname() << ' ' << max_age << std::endl << std::endl;
}

const char* FMIBook::getNicknameFromID(size_t id)
{
	size_t user_size = users.getUsersSize();

	for (size_t i = 0; i < user_size; ++i)
	{
		size_t post_size = users.getUser(i)->getPostIDsSize();
		for (size_t j = 0; j < post_size; ++j)
			if (id == users.getUser(i)->getPostID(j))
				return users.getUser(i)->getNickname();
	}


	size_t mod_size = mods.getModeratorsSize();

	for (size_t i = 0; i < mod_size; ++i)
	{
		size_t post_size = mods.getModerator(i)->getPostIDsSize();
		for (size_t j = 0; j < post_size; ++j)
			if (id == mods.getModerator(i)->getPostID(j))
				return mods.getModerator(i)->getNickname();
	}


	size_t post_size = admin.getPostIDsSize();

	for (size_t i = 0; i < post_size; ++i)
		if (id == admin.getPostID(i))
			return admin.getNickname();

	return nullptr;
}


bool FMIBook::usernameExists(const char* name)
{
	size_t users_size = users.getUsersSize();
	size_t mods_size = mods.getModeratorsSize();
	for (size_t i = 0; i < users_size; ++i)
	{
		if (!strcmp(users.getUser(i)->getNickname(), name))
			return true;
	}

	for (size_t i = 0; i < mods_size; ++i)
	{
		if (!strcmp(mods.getModerator(i)->getNickname(), name))
			return true;
	}

	if (!strcmp(admin.getNickname(), name))
		return true;

	return false;
}

bool FMIBook::isBlocked(const char* name)
{
	size_t size = blocked.getBlockedUsersSize();

	for (size_t i = 0; i < size; ++i)
		if (!strcmp(blocked.getBlockedUser(i), name))
			return true;

	return false;
}

const char * FMIBook::numToStr(size_t index)
{
	size_t temp = index;
	size_t cnt = 0;
	if (!index) cnt = 1;
	while (temp)
	{
		temp /= 10;
		++cnt;
	}

	char* str = new char[SIZE_OF_STR_POST + cnt + SIZE_OF_STR_HTML + 1];
	strncpy(str, "Post", SIZE_OF_STR_POST);

	for (size_t i = SIZE_OF_STR_POST + (cnt - 1); i >= SIZE_OF_STR_POST; --i)
	{
		str[i] = index % 10 + '0';
		index /= 10;
	}
	strncpy(str + SIZE_OF_STR_POST + cnt, ".html", SIZE_OF_STR_HTML);
	str[SIZE_OF_STR_POST + cnt + SIZE_OF_STR_HTML] = '\0';

	return str;
}

bool FMIBook::isModerator(const char* name)
{
	size_t size = mods.getModeratorsSize();
	for (size_t i = 0; i < size; ++i)
		if (!strcmp(mods.getModerator(i)->getNickname(), name))
			return true;

	return false;
}
