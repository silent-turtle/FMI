#ifndef TEXT_HDR
#define TEXT_HDR

#include"Cell.h"


class Text : public Cell
{
public:
	Text();
	Text(const char*);
	~Text();

	void viewContent() const { std::cout << text; }
	void deserialise(std::ifstream& ifs);
	void serialise(std::ofstream& ofs);
	size_t getLength() const { return text_size; }

private:
	char* text;
	size_t text_size;

	void setText(const char*);
};

#endif // TEXT_HDR
