#ifndef POST_HDR
#define POST_HDR

#include<iostream>
#include<fstream>


class Post
{
public:
	Post(const char*, size_t);
	Post(const Post&) = delete;
	Post& operator=(const Post&) = delete;
	virtual ~Post();

	virtual void createHTMLFile(std::ofstream&) const = 0;
	const char* getDescription() const { return description; }
	const size_t getID() const { return id; }

protected:
	char* description;
	const size_t id;

	void setDescription(const char*);
};

#endif //POST_HDR
