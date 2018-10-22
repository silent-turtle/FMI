#ifndef HASHTAG_HDR
#define HASHTAG_HDR

#include"Word.h"

class Hashtag : public Word
{
public:
	Hashtag() = delete;
	Hashtag(const Hashtag&) = delete;
	Hashtag(const char* str);
	Hashtag& operator=(const Hashtag&) = delete;
	~Hashtag();

	const char* viewContent() const { return content; }
	size_t compareWords(const char* str);
private:
	char* content;
	size_t content_size;

	void setContent(const char* str);
};

#endif //HASHTAG_HDR
