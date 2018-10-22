#include "ModeratorCollection.h"



ModeratorCollection::ModeratorCollection() : mods(nullptr), mods_size(0), mods_capacity(0)
{
}


ModeratorCollection::~ModeratorCollection()
{
	delete[] mods;
}

void ModeratorCollection::addModerator(const char* name, size_t num)
{
	if (mods_size >= mods_capacity)
	{
		if (!mods_size) mods_capacity = 2;
		else mods_capacity *= 2;

		Moderator** newMem = new Moderator*[mods_capacity];

		for (size_t i = 0; i < mods_size; ++i)
			newMem[i] = mods[i];

		delete[] mods;

		mods = newMem;
	}
	mods[mods_size] = new Moderator(name, num);
	++mods_size;
}

void ModeratorCollection::addPostID(const char* actor, size_t id)
{
	size_t size = getModeratorsSize();
	for (size_t i = 0; i < size; ++i)
		if (!strcmp(mods[i]->getNickname(), actor))
			mods[i]->addPostID(id);
}

void ModeratorCollection::removePostID(const char* name, size_t id)
{
	for (size_t i = 0; i < mods_size; ++i)
		if (!strcmp(mods[i]->getNickname(), name))
		{
			mods[i]->removePostID(id);
			return;
		}
}

void ModeratorCollection::print() const
{
	for (size_t i = 0; i < mods_size; ++i)
	{
		std::cout << i + 1 << " Name> " << mods[i]->getNickname()
			<< "\nAge> " << mods[i]->getAge()
			<< "\nNumber of posts>" << mods[i]->getPostIDsSize() << std::endl;
	}
}

void ModeratorCollection::renameModerator(const char* new_name, size_t index)
{
	mods[index]->rename(new_name);
}

void ModeratorCollection::removeModerator(size_t index)
{
	if (mods_size == 1)
	{
		delete mods[0];
		mods[0] = nullptr;
		--mods_size;
		return;
	}

	Moderator* temp = mods[index];
	mods[index] = mods[mods_size - 1];
	mods[mods_size - 1] = temp;

	delete mods[mods_size - 1];

	mods[mods_size - 1] = nullptr;

	--mods_size;
}

void ModeratorCollection::moderatorsInfo()
{
	for (size_t i = 0; i < mods_size; ++i)
		std::cout << mods[i]->getNickname() << " - Moderator, " 
		<< mods[i]->getPostIDsSize() << " posts.\n";
}
