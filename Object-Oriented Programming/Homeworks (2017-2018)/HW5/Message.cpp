#include "Message.h"


Message::Message() : line(nullptr), words(nullptr), words_size(0)
{
}

//Message::Message(const char* str) : line(nullptr), words(nullptr), words_size(0)
//{
//	setLine(str);
//	setWords();
//}


Message & Message::operator=(const Message& other)
{
	if (this != &other)
	{
		size_t size = strlen(other.line);

		char* newMem = new char[size + 1];

		strncpy_s(newMem, size + 1, other.line, size);
		
		if (line) delete[] line;

		line = newMem;


		Word** newMem2 = new Word*[other.words_size];

		for (size_t i = 0; i < other.words_size; ++i)
		{
			newMem2[i] = other.words[i];
			other.words[i] = nullptr;
		}

		if (words)
		{
			for (size_t i = 0; i < words_size; ++i)
				delete[] words[i];

			delete[] words;
		}

		words_size = other.words_size;
		words = newMem2;
	}
	return *this;
}

Message::~Message()
{
	clean();
}

size_t Message::compare(const char * str)
{
	size_t res = 0;
	const char* str_type = getType(str);
	for (size_t i = 0; i < words_size; ++i)
	{
		const char* word_type = getType(words[i]->viewContent());

		if (!strcmp(str_type, word_type))
			res += words[i]->compareWords(str);
	}

	return res;
}

void Message::printHashtags() const
{
	for (size_t i = 0; i < words_size; ++i)
	{
		if (!strcmp("Hashtag", getType(words[i]->viewContent())))
		{
			std::cout << words[i]->viewContent() << std::endl;
		}
	}
}

void Message::setContent(const char* str)
{
	try
	{
	setLine(str);
	setWords();
	}
	catch (std::bad_alloc& e)
	{
		clean();
		throw;
	}
	catch (const char* msg)
	{
		clean();
		throw;
	}
}

void Message::setLine(const char* str)
{
	size_t size = strlen(str);
	char* newMem = new char[size + 1];

	strncpy_s(newMem, size + 1, str, size);

	if (line) delete[] line;

	line = newMem;
}

void Message::setWords()
{
	setWordsSize();

	words = new Word*[words_size];

	size_t words_cnt = 0;
	size_t line_cnt = 0;

	while(words_cnt != words_size)
	{
		size_t symbol_cnt = 0;
		while (!isWordSymbol(line[line_cnt]))
		{
			++line_cnt;
		}

		while (isWordSymbol(line[line_cnt]))
		{
			++line_cnt;
			++symbol_cnt;
		}

		char* content = new char[symbol_cnt + 1];
		strncpy_s(content, symbol_cnt + 1, line + line_cnt - symbol_cnt, symbol_cnt);

		const char* type = getType(content);

		words[words_cnt] = WordFactory::createWord(content, type);
		++words_cnt;
	}
}

void Message::setWordsSize()
{
	size_t words_cnt = 0;
	size_t line_cnt = 0;
	while (line[line_cnt] != '\0')
	{
		size_t symbol_cnt = 0;
		while (!isWordSymbol(line[line_cnt]))
		{
			if (line[line_cnt] == '\0') break;
			++line_cnt;
		}
		while (isWordSymbol(line[line_cnt]))
		{
			++line_cnt;
			++symbol_cnt;
		}

		if (symbol_cnt) ++words_cnt;
	}

	words_size = words_cnt;
}

bool Message::isWordSymbol(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '#' || c == '-' || (c>='0' && c<='9'));
}

const char* Message::getType(const char* str) const
{
	if (str[0] == '#')
		return "Hashtag";

	size_t cnt = 0;
	while (*str != '\0')
	{
		if (*str == '-')
			++cnt;
		++str;
	}


	if (cnt == 2)
		return "Date";

	return "Simple";
}

void Message::clean()
{
	if (line) delete[] line;

	if (words)
	{
		for (size_t i = 0; i < words_size; ++i)
		{
			delete[] words[i];
			words[i] = nullptr;
		}
		delete[] words;
	}

	words_size = 0;
}
