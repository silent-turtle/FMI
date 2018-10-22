#include<iostream>
using std::cin;
using std::cout;

const short MAX_SHORT_BIT = 8 * sizeof(short);
const short MAX_BUFFER_SIZE = 80;

unsigned short* createDict(size_t num);
bool isNumber(char c);
unsigned short myatoi(const char* buf, size_t beg, size_t end);
bool isInDict(unsigned short num, unsigned short* dict, size_t dict_num);
size_t getNumbers(const char* buf, unsigned short* dict, size_t dict_num);

int main()
{
	size_t dict_num;
	cin >> dict_num;

	unsigned short* dict = createDict(dict_num);

	char c = cin.get();
	if (c != '\n') cin.putback(c);

	char buffer[MAX_BUFFER_SIZE];
	cin.getline(buffer, MAX_BUFFER_SIZE + 1);

	cout << getNumbers(buffer, dict, dict_num);

	delete[] dict;

	return 0;
}


unsigned short* createDict(size_t num)
{
	unsigned short* newMem = new(std::nothrow) unsigned short[num];
	if (!newMem)
	{
		cout << "Not enough memory!\n";
		return nullptr;
	}

	for (size_t i = 0; i < num; ++i)
	{
		do
			cin >> newMem[i];
		while (newMem[i] >= (1 << MAX_SHORT_BIT));
	}

	return newMem;
}

bool isNumber(char c)
{
	return (c >= '0' && c <= '9');
}

unsigned short myatoi(const char* buf, size_t beg, size_t end)
{
	unsigned short res = 0;
	for (size_t i = beg; i < end; ++i)
	{
		if (res * 10 + (buf[i] - '0') >= (1 << MAX_SHORT_BIT))
			return 0;

		res *= 10;
		res += buf[i] - '0';
	}

	return res;
}

bool isInDict(unsigned short num, unsigned short* dict, size_t dict_num)
{
	bool isIn = false;

	for (size_t i = 0; i < dict_num; ++i)
		if (num == dict[i])
			isIn = true;

	if (isIn) return true;

	return false;
}

size_t getNumbers(const char* buf, unsigned short* dict, size_t dict_num)
{
	size_t beg = 0, end = 0, res = 0;

	while (buf[end] != '\0')
	{
		while (!isNumber(buf[end]))
			++end;

		beg = end;

		while (isNumber(buf[end]))
			++end;

		unsigned short num = myatoi(buf, beg, end);

		if(isInDict(num, dict, dict_num))
				res += num;
	}

	return res;
}