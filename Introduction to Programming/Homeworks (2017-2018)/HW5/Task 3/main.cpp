#include<iostream>

const size_t MAX_SYMBOLS_NUM = 27;

void showPasswords(size_t num, size_t cnt, char* pass);
char* generateFirstPass(size_t num);

int main()
{
	size_t num, cnt;
	std::cin >> num;

	cnt = pow(MAX_SYMBOLS_NUM, num);

	char* pass = generateFirstPass(num);

	showPasswords(num, cnt, pass);

	return 0;
}

void showPasswords(size_t num, size_t cnt, char* pass)
{
	while (cnt != 0)
	{
		std::cout << pass << std::endl;
		--cnt;

		char choice;

		std::cout << "Do you want more passwords? Y/N\n";

		std::cin >> choice;

		if (choice == 'n' || choice == 'N')
		{
			delete[] pass;
			return;
		}
		else if (choice == 'y' || choice == 'Y')
		{

			bool isChanged = false;
			for (int i = num - 1; i >= 0 && !isChanged; --i)
			{
				if (pass[i] == '_' && !isChanged)
				{
					pass[i] = 'a';
					isChanged = true;
				}

				if (pass[i] == 'z' && !isChanged)
				{
					pass[i] = '_';
					continue;
				}

				if (!isChanged)
				{
					pass[i] += 1;
					isChanged = true;
				}
			}
		}
	}
	delete[] pass;
	std::cout << "No more!:(\n";
}


char* generateFirstPass(size_t num)
{
	char* temp = new (std::nothrow) char[num + 1];
	for (size_t i = 0; i < num; ++i)
	{
		temp[i] = '_';
	}

	temp[num] = '\0';

	return temp;
}