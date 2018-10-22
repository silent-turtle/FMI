#ifndef POST_LINK_HDR
#define POST_LINK_HDR

#include"Post.h"


class PostLink : public Post
{
public:
	PostLink(const char*, const char*, size_t);
	PostLink(const PostLink&) = delete;
	PostLink& operator=(const PostLink&) = delete;
	~PostLink();

	virtual void createHTMLFile(std::ofstream&) const;
	const char* getLink() const { return link; }

private:
	char* link;

	void setLink(const char*);
};

#endif //POST_LINK_HDR
