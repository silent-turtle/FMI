#include<iostream>

void fillArr(int*, size_t);
void swap(int&, int&);
void bubbleSort(int*, size_t);
void removeRep(int*, size_t&);
void printArr(int*, size_t);


int main()
{
	size_t n;
	std::cin >> n;

	int* arr = new (std::nothrow) int[n];
	if (!arr)
	{
		std::cout << "Not enough memory!\n";
		return 1;
	}

	fillArr(arr, n);
	bubbleSort(arr, n);
	removeRep(arr, n);
	printArr(arr, n);

	delete[] arr;

	return 0;
}


void fillArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		std::cin >> arr[i];
}

void swap(int& a, int& b)
{
	int temp = a;

	a = b;
	b = temp;
}

void bubbleSort(int* arr, size_t size)
{
	bool isSorted = true;

	do
	{
		isSorted = true;
		for (size_t i = 0; i < size - 1; ++i)
			if (arr[i] < arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				isSorted = false;
			}
	} while (!isSorted);
}

void removeRep(int* arr, size_t& size)
{
	bool hasNoRep = true;

	do
	{
		hasNoRep = true;
	for (size_t i = 0; i < size - 1; ++i)
		if (arr[i] == arr[i + 1])
		{
			hasNoRep = false;
			for (size_t j = i + 1; j < size - 1; ++j)
				arr[j] = arr[j + 1];

			--size;
		}
	} while (!hasNoRep);
}

void printArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}