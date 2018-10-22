#ifndef MESSAGE_COLLECTION_HDR
#define MESSAGE_COLLECTION_HDR

#include"Message.h"

struct CompareVal
{
	size_t val;
	size_t pos;
};


class MessageCollection
{
public:
	MessageCollection();
	MessageCollection(const MessageCollection& other);
	MessageCollection& operator=(const MessageCollection& other) = delete;
	~MessageCollection();

public:
	void setMessages(const char* path);
	void setSize(const char* path, std::ifstream& ifs);
	void deserialise(const char* path, std::ifstream& ifs);
	CompareVal* compare(const char* str);
	void printCompare(const char* str);
	void printHashtags() const;

public:
	MessageCollection& operator+=(const char* str);
	MessageCollection operator+(const char* str);
	const char* operator[](const char* str);

private:
	Message* msg;
	size_t msg_size;

private:
	void swap(CompareVal&, CompareVal&);
	void bubbleSort(CompareVal*);
	void addMessage(const char* str);
};

#endif //MESSAGE_COLLECTION_HDR
