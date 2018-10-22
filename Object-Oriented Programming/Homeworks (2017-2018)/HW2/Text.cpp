#include "Text.h"

Text::Text() : text_line(nullptr), line_cnt(0)
{
}

Text::Text(const Text& other) : line_cnt(other.line_cnt)
{
	seekText(other.text_line);
}

Text& Text::operator=(const Text& other)
{
	if (this != &other)
	{
		this->line_cnt = other.line_cnt;
		seekText(other.text_line);
	}
	return *this;
}

Text::~Text()
{
	delete[] text_line;
}

void Text::seekLineCnt(size_t num)
{
	line_cnt = num;
}

void Text::seekText(Line* line)
{
	Line* newMem = new(std::nothrow) Line[line_cnt];
	if (!newMem)
	{
		std::cout << "Not enough memory";
		return;
	}

	for (size_t i = 0; i < line_cnt; ++i)
		newMem[i] = line[i];

	if (text_line)
		delete[] text_line;
	text_line = newMem;
}

size_t Text::getNumOfLinesFromFile(const char* path)
{
	size_t cnt = 1;
	std::ifstream ifs;
	ifs.open(path, std::ios::binary);

	if (!ifs.is_open())
	{
		this->seekLineCnt(0);
		return cnt;
	}

	char c;
	while (!ifs.eof())
	{
		if (ifs) ifs.read((char*)&c, sizeof(c));
		if (c == '\n') ++cnt;
	}

	ifs.close();

	this->seekLineCnt(cnt);
	return cnt;
}

bool Text::loadTextFromFile(const char* path)
{
	getNumOfLinesFromFile(path);

	std::ifstream ifs;
	ifs.open(path);

	if (!ifs.is_open())
		return false;

	text_line = new(std::nothrow) Line[line_cnt];
	if (!text_line)
	{
		std::cout << "Not enough memory!";
		return false;
	}

	for (size_t i = 0; i < line_cnt; ++i)
	{
		char buffer[MAX_LINE_SIZE];

		if (ifs.good()) ifs.getline(buffer, MAX_LINE_SIZE);
		else return false;

		text_line[i].createLine(buffer);
	}

	ifs.close();

	return true;
}

void Text::makeHeading(size_t line_num)
{
	if (line_num < 0 || line_num > line_cnt)
	{
		std::cout << "Invalid input!";
		return;
	}

	size_t numOfDashes = 0;
	size_t size = text_line[line_num - 1].getWordArr()[0].getSizeOfWord();

	char* newMem = new char[size + 2];
	newMem[0] = '#';
	strncpy(newMem + 1, text_line[line_num - 1].getWordArr()[0].getWord(), size);
	newMem[size + 1] = '\0';

	text_line[line_num - 1].getWordArr()[0].createWord(newMem, size + 1);
}

size_t Text::getIndexOfWordWithStars(size_t line_num, size_t num, size_t num_of_stars)
{
	size_t cnt = text_line[line_num - 1].getWordCount();
	size_t pos = 1;

	while (cnt)
	{
		size_t size = text_line[line_num - 1].getWordArr()[pos - 1].getSizeOfWord();
		size_t star_cnt = 0;
		if (!num)
		{
			size_t i = 0;
			if (text_line[line_num - 1].getWordArr()[pos - 1].getWord()[i] == '*' ||
				text_line[line_num - 1].getWordArr()[pos - 1].getWord()[i] == '#')
			{
				while ((text_line[line_num - 1].getWordArr()[pos - 1].getWord()[i] == '*' ||
					text_line[line_num - 1].getWordArr()[pos - 1].getWord()[i] == '#') && i < size)
				{
					if (text_line[line_num - 1].getWordArr()[pos - 1].getWord()[i] == '*') ++star_cnt;
					++i;
				}
				if (star_cnt == num_of_stars) return pos;
			}
		}
		else
		{
			if (text_line[line_num - 1].getWordArr()[pos - 1].getWord()[size - 1] == '*')
			{
				while (text_line[line_num - 1].getWordArr()[pos - 1].getWord()[size - 1] == '*' && size)
				{
					if (text_line[line_num - 1].getWordArr()[pos - 1].getWord()[size - 1] == '*') ++star_cnt;
					--size;
				}
				if (star_cnt == num_of_stars) return pos;
			}
		}
		++pos;
		--cnt;
	}

	return 0;
}

char* Text::removeStars(char* str, size_t num_of_stars, size_t helper)
{
	size_t size = strlen(str) - num_of_stars;
	char* newMem = new char[size + 1];

	if (helper) num_of_stars = 0;

	for (size_t i = 0; i < size; ++i)
		newMem[i] = str[i + num_of_stars];

	newMem[size] = '\0';
	return newMem;
}

void Text::putStars(size_t num_of_stars, size_t line_num, size_t word_start, size_t word_end)
{
	if (line_num < 0 || line_num > line_cnt || word_start < 0
		|| word_end > text_line[line_num - 1].getWordCount() || word_start > word_end)
	{
		std::cout << "Invalid input!";
		return;
	}

	size_t size = text_line[line_num - 1].getWordArr()[word_start - 1].getSizeOfWord();
	size_t pos = 0;
	size_t numOfDashes = 0;
	char* newMem;

	size_t temp_start = word_start;
	size_t temp_end = word_end;

	size_t start = getIndexOfWordWithStars(line_num, 0, num_of_stars);
	size_t end = getIndexOfWordWithStars(line_num, 1, num_of_stars);

	if (start && end)
	{
		if (word_start >= start && word_start <= end) temp_start = 0;//checks if it's inside an interval
		if (word_end >= start && word_end <= end) temp_end = 0;
		if (word_start - 1 == end) temp_start = 0;//checks if the words on the left and right are from an interval
		if (word_end + 1 == start) temp_end = 0;
		if (word_start < start) //extends an interval if it's true
		{
			char* str = removeStars(text_line[line_num - 1].getWordArr()[start - 1].getWord(), num_of_stars, 0);
			size_t str_size = strlen(str);

			text_line[line_num - 1].getWordArr()[start - 1].createWord(str, str_size);

			delete[]str;
		}
		if (word_end > end)
		{
			char* str = removeStars(text_line[line_num - 1].getWordArr()[end - 1].getWord(), num_of_stars, 1);
			size_t str_size = strlen(str);

			text_line[line_num - 1].getWordArr()[end - 1].createWord(str, str_size);

			delete[] str;
		}
	}

	word_start = temp_start;
	word_end = temp_end;

	if (word_start == word_end)
	{
		if(word_start)
		{
			if (word_start == 1)
			{
				if (text_line[line_num - 1].getWordArr()[word_start - 1].getWord()[0] == '#')
				{
					while (text_line[line_num - 1].getWordArr()[word_start - 1].getWord()[pos] == '#')
					{
						++numOfDashes;
						++pos;
					}
				}
			}

			char* newMem = new char[size + 2 * num_of_stars + 1];

			size -= numOfDashes;

			if (text_line[line_num - 1].getWordArr()[word_start - 1].getWord()[0] == '#')
				for (size_t i = 0; i < pos; ++i)
					newMem[i] = '#';


			for (size_t i = 0; i < num_of_stars; ++i, ++pos)
				newMem[pos] = '*';

			--size;
			strncpy(newMem + pos, text_line[line_num - 1].getWordArr()[word_start - 1].getWord() + numOfDashes, size);
			pos += size;
			for (size_t i = 0; i < num_of_stars; ++i, ++pos)
				newMem[pos] = '*';

			newMem[pos++] = ' ';
			newMem[pos] = '\0';

			text_line[line_num - 1].getWordArr()[word_start - 1].createWord(newMem, size + 1 + 2 * num_of_stars + numOfDashes);

			delete[] newMem;
		}
	}

	else
	{
		if (word_start)
		{
			if (text_line[line_num - 1].getWordArr()[word_start - 1].getWord()[0] == '#')
			{
				size_t i = 0;
				while (text_line[line_num - 1].getWordArr()[0].getWord()[pos] == '#')
				{
					++numOfDashes;
					++pos;
				}
			}

			newMem = new char[size + numOfDashes + num_of_stars + 1];

			size -= numOfDashes;

			if (text_line[line_num - 1].getWordArr()[word_start - 1].getWord()[0] == '#')
				for (size_t i = 0; i < pos; ++i)
					newMem[i] = '#';


			for (size_t i = 0; i < num_of_stars; ++i, ++pos)
				newMem[pos] = '*';


			strncpy(newMem + pos, text_line[line_num - 1].getWordArr()[word_start - 1].getWord() + numOfDashes, size);
			pos += size;
			newMem[pos] = '\0';

			text_line[line_num - 1].getWordArr()[word_start - 1].createWord(newMem, size + num_of_stars + numOfDashes);

			delete[] newMem;
			newMem = nullptr;
		}

		if (word_end)
		{
			pos = 0;
			size_t size_end = text_line[line_num - 1].getWordArr()[word_end - 1].getSizeOfWord();

			newMem = new char[size_end + num_of_stars + 1];

			--size_end;
			strncpy(newMem, text_line[line_num - 1].getWordArr()[word_end - 1].getWord(), size_end);
			pos += size_end;
			for (size_t i = 0; i < num_of_stars; ++i, ++pos)
				newMem[pos] = '*';

			newMem[pos++] = ' ';
			newMem[pos] = '\0';


			text_line[line_num - 1].getWordArr()[word_end - 1].createWord(newMem, size_end + 1 + num_of_stars);

			delete[] newMem;
		}
	}
}

void Text::addNewLine(char* str)
{
	if (*str)
	{
		Line* newMem = new(std::nothrow) Line[line_cnt + 1];
		if (newMem)
		{
			for (size_t i = 0; i < line_cnt; ++i)
				newMem[i] = text_line[i];

			delete[] text_line;
			text_line = newMem;

			text_line[line_cnt].createLine(str);

			++line_cnt;
		}
		else std::cout << "Not enough memory to add a new line!";
	}
	else std::cout << "There was nothing to add!";
}

void Text::removeLine(size_t num)
{
	if (num < 0 || num > line_cnt)
	{
		std::cout << "Invalid input!";
		return;
	}

	for (size_t i = num - 1; i < line_cnt - 1; ++i)
		text_line[i] = text_line[i + 1];
	
	--line_cnt;
}

void Text::printArr()
{
	for (size_t i = 0; i < line_cnt; ++i)
	{
		Word* temp = text_line[i].getWordArr();
		size_t word_cnt = text_line[i].getWordCount();
		for (size_t j = 0; j < word_cnt; ++j)
			std::cout << temp[j].getWord();
		
		std::cout << std::endl;
	}
}

bool Text::saveTextToFile(const char* path)
{
	size_t size = strlen(path);
	char* str = new(std::nothrow) char[size - 1];
	strncpy(str, path, size - 3);
	str[size - 3] = 'm';
	str[size - 2] = 'd';
	str[size - 1] = '\0';


	std::ofstream ofs;
	ofs.open(str);

	if (!ofs.is_open())
	{
		std::cout << "The file could not be opened. The text is not saved!";
		return false;
	}

	const char* new_line = "</br> ";

	for (size_t i = 0; i < line_cnt; ++i)
	{
		size_t wordsNum = text_line[i].getWordCount();
		for (size_t j = 0; j < wordsNum; ++j)
			if (ofs.good())	ofs << text_line[i].getWordArr()[j].getWord();
		
		ofs << new_line;
	}

	ofs.close();

	return true;
}