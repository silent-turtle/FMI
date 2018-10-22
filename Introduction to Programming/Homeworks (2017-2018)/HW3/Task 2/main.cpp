#include <iostream>
#include <ctime>
using namespace std;

const int MAXALPHNUM = 26;

void printWord(char* str, size_t str_len)
{
	for (size_t i = 0; i < str_len; ++i)
	{
		cout << str[i];
	}
}

bool isEmptyWord(char* str, size_t str_len)
{

	for (size_t i = 0; i < str_len; ++i)
	{
		if (*(str+i) == '_') return true;
	}
	return false;
}

int main()
{
	srand(time(0));
	bool isSameLetter = false;
	size_t numOfTries = 0;
	size_t n = 0;
	
	char alph[MAXALPHNUM] = {};
	const char* dictionary[] = { "dayana", "sintiya", "jimin", "valentina", "youngguk", "bap" };
	const size_t rndnum = rand() % 6;
	const size_t b = strlen(dictionary[rndnum]);
	char* hangman = new (nothrow) char[b+1];
	cout <<"Total letters: " << b << endl;
	cout << numOfTries << "/5 ";
	for (int i = 0; i < b; ++i)
	{
		hangman[i] = '_';
		hangman[b] = '\0';
		cout << hangman[i];
	}
	cout << endl;
	for (int m = 0; m < b+5; ++n, ++m)
	{
		char c;
		cin >> c;
		alph[m] = c;
		for (int i = 0; i < b; ++i)
		{
			if (*(dictionary[rndnum] + i) == c)
			{
				hangman[i] = c;
				isSameLetter = true;
			}
		}
		if (!isSameLetter) ++numOfTries;
		isSameLetter = false;
		cout << numOfTries << "/5 ";
		printWord(hangman, b);
		cout << " History : ";
		printWord(alph, b+5);
		cout << endl;
		if (numOfTries >= 5)
		{
			cout << "You lose!";
			break;
		}
		else if ((numOfTries < 5) && !isEmptyWord(hangman, b)) cout << "You win!";
	}
	delete[] hangman;
	return 0;
}