#ifndef POST_PICTURE_HDR
#define POST_PICTURE_HDR

#include"Post.h"

class PostPicture : public Post
{
public:
	PostPicture(const char*, size_t);
	PostPicture(const PostPicture&) = delete;
	PostPicture& operator=(const PostPicture&) = delete;

	virtual void createHTMLFile(std::ofstream&) const;
};

#endif //POST_PICTURE_HDR
