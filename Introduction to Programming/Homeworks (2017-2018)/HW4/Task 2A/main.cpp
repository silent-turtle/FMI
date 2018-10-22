#include<iostream>
using std::cin;
using std::cout;

const short MAX_BUFF_SIZE = 80;


bool isNumber(char c);
size_t DigitPrefix(const char* str);
size_t ToInt(const char* str, size_t len);
void getNum(const char* buff, size_t*& arr, size_t& arr_size);


int main()
{
	char buff[MAX_BUFF_SIZE];

	cin.getline(buff, MAX_BUFF_SIZE + 1);

	size_t* arr = nullptr;
	size_t arr_size = 0;
	size_t res = 0;

	getNum(buff, arr, arr_size);

	cout << arr_size << '\n';

	for (size_t i = 0; i < arr_size; ++i)
	{
		cout << arr[i] << ' ';
		res += arr[i];
	}

	cout << '\n' << res;
	return 0;
}


bool isNumber(char c)
{
	return (c >= '0' && c <= '9');
}

size_t DigitPrefix(const char* str)
{
	static size_t res = 0;

	if (!isNumber(*str)) return res;

	++res;

	DigitPrefix(str + 1);
	res = 0;
}


size_t ToInt(const char* str, size_t len)
{
	static size_t res = 0;

	if (!len) return res;

	if (res * 10 + (*str - '0') > pow(2, sizeof(size_t) * 8 - 1)) return 0;

	res *= 10;
	res += *str - '0';

	ToInt(str + 1, len - 1);
	res = 0;
}

void getNum(const char* buff, size_t*& arr, size_t& arr_size)
{
	while (*buff != '\0')
	{
		while (!isNumber(*buff))
		{
			if (*buff == '\0')
				break;
			++buff;
		}

		size_t size = DigitPrefix(buff);
		size_t num = ToInt(buff, size);

		if (num)
		{

			size_t* newMem = new(std::nothrow) size_t[arr_size + 1];
			if (!newMem)
			{
				if (arr) delete[] arr;
				cout << "Not enough memory!\n";
			}
			for (size_t i = 0; i < arr_size; ++i)
				newMem[i] = arr[i];

			newMem[arr_size] = num;

			if (arr) delete[] arr;

			arr = newMem;
			++arr_size;
		}
		buff += size;
	}
}