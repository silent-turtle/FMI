#ifndef TRANSACTION_HDR
#define TRANSACTION_HDR

#include<time.h>

#include"Wallet.h"

const size_t SYSTEM_ID = ~0;

struct Transaction {
	long long time;
	long long timeOfCompletedOrder;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

size_t sizeOfTransactionFile();

Transaction* loadTransactionList(const size_t&);

Transaction* addTransactionInList(Transaction*, const size_t&, const size_t&, const size_t&, const double&);

double printCoins(Transaction*, const size_t&, const size_t&);

void saveTransactionsInFile(Transaction*, const size_t&);


#endif //TRANSACTION_HDR
