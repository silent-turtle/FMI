#include <iostream>
using namespace std;
int main()
{
	int x;
	cin >> x;
	int bit_num=0;//broi na bitovete
	int temp = x;
	while (x != 0)
	{
		bit_num++;
		x = x / 2;
	}
	x = temp;
	
	//cout << "broi bitove: " << bit_num << endl;
		for (bit_num-=1; bit_num > 0; --bit_num) 
		{
			
			//cout << "bit: " << bit_num << endl;
			int x1 = ((x >> bit_num) & 1); //tova mi izvejda stoinostta na n-tiq bit
            int x2 = ((x >> (bit_num+1))&1);
			//cout << "x1 " << x1 << endl;
			//cout << "x2 " << x2 << endl;
			if (x1==x2) 
			{
				x = x | ((x1<< bit_num) ^ (1 << bit_num)); 
				//--bit_num;
			}
		}
		cout << x;
	return 0;
}