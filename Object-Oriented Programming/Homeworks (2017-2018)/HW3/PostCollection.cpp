#include "PostCollection.h"

size_t PostCollection::id = 0;

PostCollection::PostCollection() : posts(nullptr), post_size(0), post_capacity(0)
{
}


PostCollection::~PostCollection()
{
	delete[] posts;
}

void PostCollection::addPost(const char* cmd, const char* text, const char* link_str)
{
	if (post_size == post_capacity)
	{
		if (!post_size)
			post_capacity = 1;
		else post_capacity *= 2;

		Post** newMem = new Post*[post_capacity];

		for (size_t i = 0; i < post_size; ++i)
			newMem[i] = posts[i];

		delete[] posts;

		posts = newMem;

	}

	if (!strcmp(cmd, "[image]"))
		posts[post_size] = new PostPicture(text, id);

	if (!strcmp(cmd, "[url]"))
		posts[post_size] = new PostLink(text, link_str, id);

	if (!strcmp(cmd, "[text]"))
		posts[post_size] = new PostText(text, id);

	increaseID();

	++post_size;
}

void PostCollection::removePost(size_t index)
{
	if (post_size == 1)
	{
		if (index == posts[0]->getID())
		{
			delete posts[0];
			posts[0] = nullptr;
			--post_size;
			return;
		}
	}

	for (size_t i = 0; i < post_size; ++i)
		if (index == posts[i]->getID())
		{
			Post* temp = posts[i];
			posts[i] = posts[post_size - 1];
			posts[post_size - 1] = temp;

			delete temp;
			posts[post_size - 1] = nullptr;
			--post_size;

			return;
		}

	std::cout << "There's no such post!\n";
}

void PostCollection::createHTMLFile(size_t id, std::ofstream& ofs)
{
	for (size_t i = 0; i < post_size; ++i)
	{
		if (id == posts[i]->getID())
			posts[i]->createHTMLFile(ofs);
	}
}

bool PostCollection::postExists(size_t id)
{
	for (size_t i = 0; i < post_size; ++i)
	{
		if (id == posts[i]->getID())
			return true;
	}

	return false;
}
