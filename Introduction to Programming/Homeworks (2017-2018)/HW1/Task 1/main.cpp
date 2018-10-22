#include <iostream>
using namespace std;
int main()
{
	unsigned int num;
	int previous = 0, current = 0, next = 0;
	bool isSaw = true, isNotSaw = false;

	cin >> num;

	if ((num > 1000000000) && (num < 0))
		cout << "The number should be between 0 and 1 000 000 000.";
	else
	{
		if (num == 2)
		{
			cin >> current >> next;

			cout << "yes";

		}
		else
		{
			for (int i = 0; i < num; i++)
			{
				previous = current;
				current = next;
				cin >> next;

				if (((previous >= current) && (current <= next)) || ((previous <= current) && (current >= next)))
					isSaw = true;
				else
					isNotSaw = false;
			}

			if (isNotSaw)
				cout << "yes";
			else
				cout << "no";
		}
	}
	return 0;
}