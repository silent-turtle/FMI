#ifndef DATE_HDR
#define DATE_HDR

#include"Word.h"

class Date : public Word
{
public:
	Date() = delete;
	Date(const char* str);
	Date(const Date&) = delete;
	Date& operator=(const Date&) = delete;
	~Date();

public:
	const char* viewContent() const { return content; }
	size_t compareWords(const char* str);

private:
	char* content;
	size_t content_size, day, month, year;

private:
	void setContent(const char* str);
	void setDate();
	size_t strToInt(const char* str, size_t& beg, char end);
	bool isLeapYear(size_t year);
	bool isValidDate();
	size_t dateToDayOfYear(size_t d, size_t m);
};

#endif//DATE_HDR
