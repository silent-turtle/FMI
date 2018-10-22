#include<iostream>


int** createMatrix(size_t row, size_t col);
void clean(int**, size_t);
bool isBeautifulRow(int*, size_t);
void fillMat(int**, size_t, size_t);
size_t getNumOfOnes(int num);
int* getBeautifulRows(int** arr, size_t row, size_t col, size_t& size);

int main()
{
	size_t n, m;
	std::cin >> n >> m;

	int** arr = createMatrix(n, m);
	fillMat(arr, n, m);

	size_t newArrSize = 0;
	int* newArr = getBeautifulRows(arr, n, m, newArrSize);

	for (size_t i = 0; i < newArrSize; ++i)
		std::cout << newArr[i] << ' ';

	delete[] arr;
	delete[] newArr;

	return 0;
}


int** createMatrix(size_t row, size_t col)
{
	int** newMem = new(std::nothrow) int*[row];

	if (!newMem)
	{
		std::cout << "Not enough memory!\n";
		return nullptr;
	}

	for (size_t i = 0; i < row; ++i)
	{
		newMem[i] = new(std::nothrow) int[col];

		if (!newMem[i])
		{
			clean(newMem, i);
			return nullptr;
		}
	}

	return newMem;
}

void clean(int** arr, size_t size)
{
	for (size_t i = size; i >= 0; --i)
		delete[] arr[i];

	delete[] arr;
}

bool isBeautifulRow(int* arr, size_t size)
{
	size_t cnt = 0;
	for (size_t i = 0; i < size; ++i)
	{
		cnt += getNumOfOnes(arr[i]);
	}

	if (cnt % 2)
		return false;

	return true;
}

size_t getNumOfOnes(int num)
{
	size_t res = 0;

	for (size_t i = 0; i < 32; ++i)
	{
		res += ((num>>i) & 1);
	}

	return res;
}

void fillMat(int** arr, size_t row, size_t col)
{
	for (size_t i = 0; i < row; ++i)
		for (size_t j = 0; j < col; ++j)
			std::cin >> arr[i][j];
}

int* getBeautifulRows(int** arr, size_t row, size_t col, size_t& size)
{
	int* newMem = nullptr;
	size_t cnt = 0;
	for (size_t i = 0; i < row; ++i)
	{
		if (isBeautifulRow(arr[i], col))
		{
			++cnt;
			int* temp = new (std::nothrow) int[cnt*col];

			if (!temp)
			{
				std::cout << "Not enough memory!\n";
				return nullptr;
			}

			for (size_t j = 0; j < (cnt - 1)*col; ++j)
				temp[j] = newMem[j];

			for (size_t j = (cnt - 1)*col, k = 0; j < cnt*col; ++j, ++k)
				temp[j] = arr[i][k];

			delete[] newMem;
			newMem = temp;

			size = cnt * col;
		}
	}
	return newMem;
}