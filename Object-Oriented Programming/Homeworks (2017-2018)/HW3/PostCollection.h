#ifndef POST_COLLECTION_HDR
#define POST_COLLECTION_HDR


#include"Post.h"
#include"PostPicture.h"
#include"PostLink.h"
#include"PostText.h"

class PostCollection
{
public:
	PostCollection();
	PostCollection(const PostCollection&) = delete;
	PostCollection& operator=(const PostCollection&) = delete;
	~PostCollection();


	void addPost(const char* cmd, const char* text, const char* link_str = nullptr);
	void removePost(size_t);

	void createHTMLFile(size_t, std::ofstream&);

	const Post* getPost(size_t index) const { return posts[index - 1]; }
	const size_t getPostSize() const { return post_size; }

	bool postExists(size_t);

private:
	Post** posts;
	size_t post_size;
	size_t post_capacity;
	static size_t id;
	static size_t increaseID() { return ++id; }
};

#endif //POST_COLLECTION_HDR
