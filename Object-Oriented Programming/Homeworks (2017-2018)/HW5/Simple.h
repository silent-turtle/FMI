#ifndef SIMPLE_HDR
#define SIMPLE_HDR

#include"Word.h"

class Simple : public Word
{
public:
	Simple() = delete;
	Simple(const Simple&) = delete;
	Simple(const char* str);
	Simple& operator=(const Simple&) = delete;
	~Simple();
	const char* viewContent() const { return content; }
	size_t compareWords(const char* str);

private:
	char* content;
	size_t content_size;
	
	bool isSameLetter(char a, char b);
	void setContent(const char* str);
};

#endif //SIMPLE_HDR
