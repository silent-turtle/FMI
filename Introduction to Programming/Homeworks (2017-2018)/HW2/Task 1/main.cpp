#include<iostream>
using namespace std;

const int MAXN = 11;

void printTable(int arr[][MAXN], int size);
void isMagicSquare(int arr[][MAXN], int size);

int main()
{
	int array[MAXN][MAXN], num;
	do
	{
		cout << "Enter size:\n";
		cin >> num;
		if (num < 0 || num >= MAXN) cout << "Invalid size of array!\n" << endl;
	}
		while (num < 0 || num >= MAXN);
	
	printTable(array, num);
	isMagicSquare(array, num);
	return 0;
}


void printTable(int arr[][MAXN], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cin >> arr[i][j];
		}
	}
}

void isMagicSquare(int arr[][MAXN], int size)
{
	bool isMagicSquare = true;
	int sumRow1 = 0, sumRow2 = 0, 
	sumCol1 = 0, sumCol2 = 0,
	sumDiagonal1 = 0, sumDiagonal2 = 0;

	for (int j = 0; j < size; ++j) sumRow1 += arr[0][j];

	for (int i = 0; i < size; ++i) sumCol1 += arr[i][0];
	
	if (sumRow1 != sumCol1) isMagicSquare = false;

	for (int i = 1; i < size; ++i)
	{
		sumRow2 = 0;
		for (int j = 0; j < size; ++j) sumRow2 += arr[i][j];
		
		if (sumRow1 != sumRow2) isMagicSquare = false;
		sumRow1 = sumRow2;
	}


	for (int j = 1; j < size; ++j)
	{
		sumCol2 = 0;
		for (int i = 0; i < size; ++i) sumCol2 += arr[i][j];
		
		if (sumCol1 != sumCol2) isMagicSquare = false;
		sumCol1 = sumCol2;
	}

	for (int i = 0; i < size; ++i) sumDiagonal1 += arr[i][i];

	if (sumDiagonal1 != sumRow1) isMagicSquare = false;


	int k = 1;
	for (int i = size - 1; i >= 0; --i)
	{
		for (int j = k-1; j < k && j < size; ++j) sumDiagonal2 += arr[i][j];
		++k;
	}

	if (sumDiagonal1 != sumDiagonal2) isMagicSquare = false;

	if (isMagicSquare) cout<<"True";
	else cout << "False";
}