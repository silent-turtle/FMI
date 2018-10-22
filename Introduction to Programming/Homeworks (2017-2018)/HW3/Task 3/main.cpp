#include <iostream>
#include <ctime>
#include <string.h>
using namespace std;

void mystrcpy(char* dest, const char* src);
void mystrcat(char* dest, const char* src);
void printExclMarks(char* str, size_t num);
void clean(char** matrix, int n);

int main()
{
	srand(time(0));
	
	int n;
	cout << "Enter number of headings: ";
	cin >> n;

	const char* subject[] = {"Lekar", "Maika", "Uchenik", "Pevec", "Semeistvo", "Bastun", "Spondjbob", };
	const char* verb[] = {"kiha", "namiga na", "otkradna", "prepyna", "izkreshtq", "preskacha", "poluchi", "gleda", "sviri varhu", "tancuva varhu"};
	const char* object[] = { "maimuna", "kniga", "kola", "kolelo", "portokal", "magazin", "garderob", "chehal", "patica" };
	const char* exclam[] = {"Potres", "Shok", "Skandal", "Izvanredno","Neveroqtno",};
	
	char** sentence = new(nothrow) char*[n];
	if (sentence == NULL) cout << "No memory";

	for (int i = 0; i < n; ++i)
	{
		const size_t subRndNum = rand() % 7;
		const size_t sizeOfSubWord = strlen(subject[subRndNum]);

		const size_t verbRndNum = rand() % 10;
		const size_t sizeOfVerbWord = strlen(verb[verbRndNum]);

		const size_t objRndNum = rand() % 9;
		const size_t sizeOfObjWord = strlen(object[objRndNum]);
			
		const size_t exclamRndNum = rand() % 5;
		const size_t sizeOfEclamWord = strlen(exclam[exclamRndNum]);
			
		const size_t numOfExclMarks = (rand() % 7) + 3;
			
		const size_t sizeOfHeadline = sizeOfSubWord + sizeOfVerbWord + sizeOfEclamWord + sizeOfObjWord + numOfExclMarks;
		
		char* exclamsym = new (nothrow) char[numOfExclMarks+1];
		exclamsym[numOfExclMarks] = '\0';
		printExclMarks(exclamsym, numOfExclMarks);
			

		sentence[i] = new(nothrow) char[sizeOfHeadline + 4];
		if (sentence[i] == NULL)
		{
			clean(sentence, i);// deletes the sentences before that as well
			cout << "No memory";
		}
		
		mystrcpy(sentence[i], exclam[exclamRndNum]);
		mystrcat(sentence[i], exclamsym);
		mystrcat(sentence[i], " ");
		mystrcat(sentence[i], subject[subRndNum]);
		mystrcat(sentence[i], " ");
		mystrcat(sentence[i], verb[verbRndNum]);
		mystrcat(sentence[i], " ");
		mystrcat(sentence[i], object[objRndNum]);
		cout << sentence[i] << endl;
		
		delete[] exclamsym;
		
	}
	clean(sentence, n);
	return 0;
}

void mystrcpy(char* dest, const char* src)
{
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = *src;
}

void mystrcat(char* dest, const char* src)
{
	size_t s = strlen(dest);
	size_t i = 0;
	while (src[i])
	{
		dest[s + i] = src[i];
		++i;
	}
	dest[s + i] = '\0';
}

void printExclMarks(char* str, size_t num)
{
	for (int i = 0; i < num; ++i)
	{
		str[i] = '!';
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