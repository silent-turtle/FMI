#include"Wallet.h"

size_t sizeOfWalletFile()
{
	std::ifstream ifs;
	ifs.open("wallets.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return 0;
	}
	 
	ifs.seekg(-4, std::ios::end);
	size_t num;
	ifs.read((char*)&num, sizeof(num));

	ifs.close();

	return num;
}


Wallet* loadWalletList(const size_t& num)
{
	Wallet* wallets = new (std::nothrow) Wallet[num];
	if (!wallets)
	{
		return NULL;
	}

	std::ifstream ifs;
	ifs.open("wallets.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return NULL;
	}

	for (size_t i = 0; i < num; ++i)
	{
		size_t size;
		ifs.read((char*)&size, sizeof(size));
		ifs.read(wallets[i].owner, size);
		wallets[i].owner[size] = '\0';
		ifs.read((char*)&wallets[i].fiatMoney, sizeof(wallets[i].fiatMoney));
		ifs.read((char*)&wallets[i].completeOrders, sizeof(wallets[i].completeOrders));
		ifs.read((char*)&wallets[i].id, sizeof(wallets[i].id));
	}

	ifs.close();

	return wallets;
}

Wallet* addWalletInList(Wallet* w, const size_t& num)
{
	Wallet* newMem = new(std::nothrow) Wallet[num];
	if (!newMem)
	{
		return NULL;
	}

	for (size_t i = 0; i < num - 1; ++i) //copies the previous wallets
	{
		newMem[i].id = w[i].id;
		newMem[i].fiatMoney = w[i].fiatMoney;
		size_t size = strlen(w[i].owner);
		strncpy_s(newMem[i].owner, w[i].owner, size);
		newMem[i].completeOrders = w[i].completeOrders;
	}

	char* str = strtok(NULL, " ");
	newMem[num - 1].fiatMoney = atof(str);

	str = strtok(NULL, "\n");
	size_t size_of_name = strlen(str);
	strncpy_s(newMem[num - 1].owner, str, size_of_name);

	newMem[num - 1].id = num;
	newMem[num - 1].completeOrders = 0;

	delete[]w;
	w = newMem;

	std::cout << std::endl << std::endl;

	return w;
}

void saveWalletsInFile(Wallet* w, const size_t& w_num)
{
	std::ofstream ofs;
	ofs.open("wallets.dat", std::ios::binary | std::ios::trunc);
	if (!ofs.is_open())
	{
		std::cout << "The file 'wallets.dat' could not be opened!";
		return;
	}

	for (size_t i = 0; i < w_num; ++i)
	{
		size_t size = strlen(w[i].owner);
		ofs.write((const char*)&size, sizeof(size));
		ofs.write(w[i].owner, size);
		ofs.write((const char*)&w[i].fiatMoney, sizeof(w[i].fiatMoney));
		ofs.write((const char*)&w[i].completeOrders, sizeof(w[i].completeOrders));
		ofs.write((const char*)&w[i].id, sizeof(w[i].id));
	}

	ofs.close();
}