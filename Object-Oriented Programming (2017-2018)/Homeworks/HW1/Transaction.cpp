#include"Transaction.h"


size_t sizeOfTransactionFile()
{
	std::ifstream ifs;
	ifs.open("transactions.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return 0;
	}

	ifs.seekg(0, std::ios::end);
	size_t num = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	ifs.close();

	size_t cnt = num / sizeof(Transaction);

	return cnt;
}

Transaction* loadTransactionList(const size_t& num)
{
	Transaction* t = new(std::nothrow) Transaction[num];
	if (!t)
	{
		return NULL;
	}

	std::ifstream ifs;
	ifs.open("transactions.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return NULL;
	}

	for (size_t i = 0; i < num; ++i)
	{
		ifs.read((char*)&t[i].time, sizeof(long long));
		ifs.read((char*)&t[i].timeOfCompletedOrder, sizeof(long long));
		ifs.read((char*)&t[i].senderId, sizeof(size_t));
		ifs.read((char*)&t[i].receiverId, sizeof(size_t));
		ifs.read((char*)&t[i].fmiCoins, sizeof(double));
	}

	ifs.close();

	return t;
}

Transaction* addTransactionInList(Transaction* t, const size_t& t_num,
	const size_t& seller_id, const size_t& buyer_id, const double& coins)
{
	Transaction* newMem = new(std::nothrow) Transaction[t_num];
	if (!newMem)
	{
		return NULL;
	}

	for (size_t i = 0; i < t_num - 1; ++i)
	{
		newMem[i].time = t[i].time;
		newMem[i].timeOfCompletedOrder = t[i].timeOfCompletedOrder;
		newMem[i].receiverId = t[i].receiverId;
		newMem[i].senderId = t[i].senderId;
		newMem[i].fmiCoins = t[i].fmiCoins;
	}

	newMem[t_num - 1].time = time(0);
	newMem[t_num - 1].timeOfCompletedOrder = 0;
	newMem[t_num - 1].senderId = seller_id;
	newMem[t_num - 1].receiverId = buyer_id;
	newMem[t_num - 1].fmiCoins = coins;

	delete[]t;
	t = newMem;

	return t;
}

double printCoins(Transaction* t, const size_t& t_num, const size_t& id)
{
	double res = 0;
	for (size_t i = 0; i < t_num; ++i)
	{
		if (t[i].receiverId == id)
		{
			res += t[i].fmiCoins;
		}
		if (t[i].senderId == id)
		{
			res -= t[i].fmiCoins;
		}
	}

	return res;
}

void saveTransactionsInFile(Transaction* t, const size_t& t_num)
{
	std::ofstream ofs;
	ofs.open("transactions.dat", std::ios::binary | std::ios::trunc);
	if (!ofs.is_open())
	{
		std::cout << "The file 'transactions.dat' could not be opened!";
		return;
	}

	for (size_t i = 0; i < t_num; ++i)
	{
		ofs.write((const char*)&t[i].time, sizeof(long long));
		ofs.write((const char*)&t[i].timeOfCompletedOrder, sizeof(long long));
		ofs.write((const char*)&t[i].senderId, sizeof(size_t));
		ofs.write((const char*)&t[i].receiverId, sizeof(size_t));
		ofs.write((const char*)&t[i].fmiCoins, sizeof(double));
	}

	ofs.close();
}