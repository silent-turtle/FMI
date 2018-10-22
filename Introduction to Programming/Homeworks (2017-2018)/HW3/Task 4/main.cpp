#include <iostream>
using namespace std;

const int MAX_WORDS_SIZE = 40;
const int MAX_CROSSWORD_SIZE = 100;

void fillCrossword(char matrix[][MAX_CROSSWORD_SIZE], size_t size, size_t col);
void fillDictionary(char** str, size_t size);
void clean(char** matrix, int n); 
char** createMatrix(int n, int m); 
bool checkDic(char** dic, char* word, size_t k);
bool isCrossword(char matrix[][MAX_CROSSWORD_SIZE], char** dic, size_t k, size_t row); 
void transposeOfMatrix(char matrix[][MAX_CROSSWORD_SIZE],
	char matrix2[][MAX_CROSSWORD_SIZE], size_t row, size_t col);

int main()
{
	size_t k;
	cin >> k;
	char** dictionary = createMatrix(k, MAX_WORDS_SIZE);
	if (!dictionary) 
	{
		cout << "Not enough memory!";
		return 1;
	}
	else
	{
		fillDictionary(dictionary, k);
		cout << endl;
		size_t row, col;
		char crossword[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE];
		char crossword_t[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE];
		cout << "rows and cols:";
		cin >> row >> col;
		cout << endl;
		fillCrossword(crossword, row + 1, col+1);
		transposeOfMatrix(crossword_t, crossword, row+1, col+1);
		cout << endl;
		if (isCrossword(crossword, dictionary, k, row) && 
			isCrossword(crossword_t, dictionary, k, col)) cout << "True";
		else cout << "False";
		clean(dictionary, k);
		return 0;
	}
}

void fillCrossword(char matrix[][MAX_CROSSWORD_SIZE], size_t size, size_t col)
{
	char c = cin.get();
	if (c != '\n') cin.putback(c);
	for (size_t i = 0; i < size - 1; ++i)
	{
		cin.getline(matrix[i], col);
	}
}

void fillDictionary(char** str, size_t size)
{
	char c = cin.get();
	if (c != '\n') cin.putback(c);
	for (size_t i = 0; i < size; ++i)
	{
		cin.getline(str[i], MAX_WORDS_SIZE);
	}
}

void clean(char** matrix, int n)
{
	for (int i = 0; i < n; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

char** createMatrix(int n, int m)
{
	char** matrix = new(nothrow) char*[n];
	if (!matrix)
	{
		delete[]matrix;
		return NULL;
	}
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new(nothrow) char[m];
		if (!matrix[i])
		{
			clean(matrix, i);
			return NULL;
		}
	}
	return matrix;
}

bool checkDic(char** dic, char* word, size_t k)
{
	for (size_t i = 0; i < k; i++)
		if (strcmp(word, dic[i]) == 0)
			return true;
	return false;
}

bool isCrossword(char matrix[][MAX_CROSSWORD_SIZE], char** dic, size_t k, size_t row)
{
	for (size_t i = 0; i < row; ++i)
	{
		char* currWord = strtok(matrix[i], "*");

		while (currWord != nullptr)
		{
			size_t a = strlen(currWord);
			if (a >= 2)
				if (!(checkDic(dic, currWord, k)))
					return false;
			currWord = strtok(nullptr, "*");
		}
	}
	return true;
}

void transposeOfMatrix(char matrix[][MAX_CROSSWORD_SIZE], 
	char matrix2[][MAX_CROSSWORD_SIZE], size_t row, size_t col)//row_1, col+1 7 8
{
	for (size_t i = 0; i < col; ++i)
	{
		for (size_t j = 0; j < row; ++j)
		{
			matrix[i][j] = matrix2[j][i];
		}
		matrix[i][row - 1] = '\0';
	}
}