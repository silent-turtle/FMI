#ifndef MESSAGE_HDR
#define MESSAGE_HDR

#include"Word.h"
#include"WordFactory.h"

class Message
{
public:
	Message();
	//Message(const char* str);
	Message(const Message&) = delete;
	Message& operator=(const Message&);
	~Message();


	size_t compare(const char* str);
	void printHashtags() const;
	const char* getLine() const { return line; }
	void setContent(const char* str);

private:
	char* line;
	Word** words;
	size_t words_size;

	void setWords();
	void setWordsSize();
	void setLine(const char* str);
	bool isWordSymbol(char c);
	const char* getType(const char* str) const;
	void clean();
};

#endif //MESSAGE_HDR
