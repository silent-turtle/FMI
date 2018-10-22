#ifndef TEXT_HDR
#define TEXT_HDR

#include"Line.h"

class Text
{
public:
	Text();
	Text(const Text&);
	Text& operator=(const Text&);
	~Text();

	bool loadTextFromFile(const char* path);
	bool saveTextToFile(const char* path);

	void makeHeading(size_t line_num);
	void putStars(size_t num_of_stars, size_t line_num, size_t word_start, size_t word_end);
	void addNewLine(char * str);
	void removeLine(size_t num);


	void printArr();


private:
	Line* text_line;
	size_t line_cnt;

	void seekLineCnt(size_t num);
	void seekText(Line* line);
	size_t getIndexOfWordWithStars(size_t line_num, size_t num, size_t num_of_stars);
	char* removeStars(char * str, size_t num_of_stars, size_t helper);
	size_t getNumOfLinesFromFile(const char* path);
};

#endif //TEXT_HDR
