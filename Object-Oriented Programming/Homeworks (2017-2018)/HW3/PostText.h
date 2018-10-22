#ifndef POST_TEXT_HDR
#define POST_TEXT_HDR

#include"Post.h"

class PostText : public Post
{
public:
	PostText(const char*, size_t);
	PostText(const PostText&) = delete;
	PostText& operator=(const PostText&) = delete;
	
	virtual void createHTMLFile(std::ofstream&) const;
};

#endif //POST_TEXT_HDR
