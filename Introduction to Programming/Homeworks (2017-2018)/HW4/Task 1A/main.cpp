#include<iostream>
using std::cin;
using std::cout;

const size_t MAX_WORD_SIZE = 40;
const size_t MAX_BUFF_SIZE = 80;


void clear(char**, size_t);
char** createDict(size_t num);
void reverseWords(char* buffer, char** dict, size_t dict_num);
bool isLetter(char c);
bool isFromDict(char* buffer, size_t beg, size_t end, char** dict, size_t dict_num);
void reverseWord(char* buffer, size_t beg, size_t end);
void reverseWords(char* buffer, char** dict, size_t dict_num);

int main()
{
	size_t dict_num;
	cin >> dict_num;

	char** dict = createDict(dict_num);

	char c = cin.get();
	if (c != '\n') cin.putback(c);

	char buffer[MAX_BUFF_SIZE];
	cin.getline(buffer, MAX_BUFF_SIZE + 1);

	reverseWords(buffer, dict, dict_num);

	cout << buffer;

	clear(dict, dict_num);

	return 0;
}


void clear(char** arr, size_t n)
{
	for (int i = n - 1; i >= 0; --i)
		delete arr[i];

	delete[] arr;
}

char** createDict(size_t num)
{
	char** newMem = new(std::nothrow) char*[num];
	if (!newMem)
	{
		cout << "Not enough memory!\n";
		return nullptr;
	}

	for (size_t i = 0; i < num; ++i)
	{
		char buffer[MAX_WORD_SIZE];
		size_t size = 0;

		char c = cin.get();
		if (c != '\n') cin.putback(c);

		cin.getline(buffer, MAX_WORD_SIZE + 1);

		size = strlen(buffer);

		newMem[i] = new(std::nothrow) char[size + 1];
		if (!newMem[i])
		{
			clear(newMem, i);
			cout << "Not enough memory!\n";
			return nullptr;
		}

		strncpy_s(newMem[i], size + 1, buffer, size);
	}

	return newMem;
}

bool isLetter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isFromDict(char* buffer, size_t beg, size_t end, char** dict, size_t dict_num)
{
	for (size_t i = 0; i < dict_num; ++i)
	{
		bool isSame = true;

		size_t size = strlen(dict[i]);
		if (size != (end - beg))
			isSame = false;
		else
		{
			for (size_t j = 0; beg < end && j < size; ++j, ++beg)
			{
				if (buffer[beg] != dict[i][j])
				{
					isSame = false;
					break;
				}
			}
		}

		if (isSame) return true;
	}

	return false;
}

void reverseWord(char* buffer, size_t beg, size_t end)
{
	int cnt = (end - beg) / 2;
	while (cnt >= 0)
	{
		char c = buffer[beg];
		buffer[beg] = buffer[end];
		buffer[end] = c;
		++beg;
		--end;
		--cnt;
	}
}

void reverseWords(char* buffer, char** dict, size_t dict_num)
{
	size_t beg = 0, end = 0;

	while (buffer[end] != '\0')
	{
		while (buffer[end] == ' ')
			++end;

		beg = end;

		while (buffer[end] != ' ' && buffer[end] != '\0')
			++end;

		if (isFromDict(buffer, beg, end, dict, dict_num))
			reverseWord(buffer, beg, end - 1);
	}
}
