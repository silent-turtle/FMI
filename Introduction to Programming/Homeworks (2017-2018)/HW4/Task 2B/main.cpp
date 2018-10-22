#include<iostream>
using std::cin;
using std::cout;

bool isSubsequent(const int* s1, size_t len1, const int* s2, size_t len2);
size_t IncreasingPrefixLength(const int* s, size_t len);
void fillArr(int* arr, size_t size);
size_t setSize();

int main()
{
	int s1[100], s2[100];
	size_t n1, n2;

	n1 = setSize();
	fillArr(s1, n1);

	n2 = setSize();
	fillArr(s2, n2);

	if (isSubsequent(s1, n1, s2, n2))
		cout << "true";
	else cout << "false";
	
	cout << std::endl;

	cout << IncreasingPrefixLength(s1, n1) << std::endl;

	cout << IncreasingPrefixLength(s2, n2) << std::endl;

	return 0;
}

bool isSubsequent(const int* s1, size_t len1, const int* s2, size_t len2)
{
	if (len1 == 0) return true;
	if (len2 == 0 && len1 != 0) return false;

	if (*s1 == *s2) isSubsequent(s1 + 1, len1 - 1, s2 + 1, len2 - 1);
	else isSubsequent(s1, len1, s2 + 1, len2 - 1);
}

size_t IncreasingPrefixLength(const int* s, size_t len)
{
	static size_t res = 1;


	if (*s < *(s + 1))
	{
		++res;
		if (len == 2) return res;
		IncreasingPrefixLength(s + 1, len - 1);
	}
	else return res;
	res = 1;
}

void fillArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		cin >> arr[i];
}

size_t setSize()
{
	size_t n;

	do
	{
		cin >> n;
	} while (n > 100);

	return n;
}