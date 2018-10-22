#ifndef WALLET_HDR
#define WALLET_HDR


#include<iostream>
#include<fstream>
#include"Constants.h"

struct Wallet {
	char owner[256];
	unsigned id;
	unsigned completeOrders;
	double fiatMoney;
};


size_t sizeOfWalletFile();

Wallet* loadWalletList(const size_t&);

Wallet* addWalletInList(Wallet*, const size_t&);

void saveWalletsInFile(Wallet*, const size_t&);


#endif //WALLET_HDR
