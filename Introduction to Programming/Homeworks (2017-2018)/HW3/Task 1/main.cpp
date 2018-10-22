#include <iostream>
using namespace std;

const size_t MAX_N = 1024;

bool isDigit(char c);
size_t numBeforeDigits(char* str);
int myatoi(char*&str, size_t & i);
size_t sizeOfBrackets(char* str, size_t start, size_t&end, size_t& i);
size_t restOfElemCount(char* str, size_t& n);
void elemCopy(char*& dest, char* src, size_t start, size_t end, size_t num);
char* dynamicConcat(char*& dest, const char* src, char* src2, size_t i);// taken from practice
bool LettersOnly(char* str);
void decompress(char* str);


int main()
{
	char str[MAX_N];
	cin.getline(str, MAX_N);
	decompress(str);
	return 0;
}

bool isDigit(char c) {

	return c >= '0' && c <= '9';
}

size_t numBeforeDigits(char* str)
{
	size_t i = 0;
	while (!isDigit(str[i]))
	{
		++i;
	}
	return i;
}

int myatoi(char*&str, size_t & i)
{
	int res = 0;
	while (str[i] != '(')
	{
		res *= 10;
		res += str[i] - '0';
		++i;
	}
	return res;
}

size_t sizeOfBrackets(char* str, size_t start, size_t&end, size_t& i)
{
	size_t isOpened = 1;
	while (isOpened)
	{
		if (str[i] == '(') ++isOpened;
		if (str[i] == ')')
		{
			--isOpened;
			end = i;
		}
		++i;
	}
	return end - start;
}

size_t restOfElemCount(char* str, size_t& n)
{
	while (str[n] != '\0')
	{
		++n;
	}
	return n;
}

void elemCopy(char*& dest, char* src, size_t start, size_t end, size_t num)
{
	size_t m = 0;
	while (m != num)
	{
		for (size_t k = start; k < end; ++k)
		{
			dest[m] = src[k];
			++m;
		}
	}
}

char* dynamicConcat(char*& dest, const char* src, char* src2, size_t i)
{
	char* newMemBuff = new (std::nothrow) char[strlen(dest) + i + 1];

	if (newMemBuff == nullptr)
		cout << "Not enough memory";

	strcpy(newMemBuff, dest);
	strcat(newMemBuff, src);
	strcat(newMemBuff, src2);

	delete[] dest;

	dest = newMemBuff;
	return dest;
}

bool LettersOnly(char* str)
{
	bool hasLettersOnly = true;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 'A' || str[i] > 'Z') hasLettersOnly = false;
		++i;
	}
	if (hasLettersOnly) return true;
	else return false;
}

void decompress(char* str)
{
	if (LettersOnly(str))
	{
		cout << str;
		return;
	}

	size_t i = numBeforeDigits(str);
	char* res = new(nothrow)char[i + 1];
	strncpy(res, str, i);
	res[i] = '\0';

	size_t toCpy = myatoi(str, i);
	++i; // since the input should be correct, I skip the index where the '(' symbol is

	size_t startOfBrackets = i;
	size_t endOfBrackets;
	size_t numInBrackets = sizeOfBrackets(str, startOfBrackets, endOfBrackets, i);

	int restNum = restOfElemCount(str, i);

	size_t newSize = toCpy * numInBrackets;
	size_t totalSize = newSize + restNum;

	char* newres = new(nothrow) char[newSize + 1];
	if (!newres) cout << "Not enough memory in newres";
	elemCopy(newres, str, startOfBrackets, endOfBrackets, newSize);
	newres[newSize] = '\0';

	res = dynamicConcat(res, newres, str + endOfBrackets + 1, totalSize);
	delete[] newres;
	str = res;
	decompress(str);
	delete[] res;
}
