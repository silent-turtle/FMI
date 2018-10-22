#ifndef MODERATOR_COLLECTION_HDR
#define MODERATOR_COLLECTION_HDR

#include"Moderator.h"

class ModeratorCollection
{
public:
	ModeratorCollection();
	ModeratorCollection(const ModeratorCollection&) = delete;
	ModeratorCollection& operator=(const ModeratorCollection&) = delete;
	~ModeratorCollection();

	void addModerator(const char*, size_t);
	void addPostID(const char*, size_t);
	void removePostID(const char*, size_t);
	void print() const;
	void renameModerator(const char*, size_t);
	void removeModerator(size_t);

	void moderatorsInfo();

	const Moderator* getModerator(size_t index) { return mods[index]; }
	const size_t getModeratorsSize() const { return mods_size; }

private:
	Moderator** mods;
	size_t mods_size;
	size_t mods_capacity;
};

#endif //MODERATOR_COLLECTION_HDR
