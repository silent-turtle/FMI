#ifndef ORDER_HDR
#define ORDER_HDR

#include"Transaction.h"


struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};


size_t sizeOfOrderFile();

Order* loadOrdersInList(size_t&);

Order::Type typeValue(char*);

Order* addOrderInList(Order*, size_t&, Wallet*, const size_t&, Transaction*&, size_t&);

bool addNewOrder(Order&, Wallet*, const size_t&, Transaction*, const size_t&);

size_t numCnt(long long);

void createPathStr(char[], long long, const size_t&, size_t, const size_t&);

void moveUnfinishedOrder(Order*, const size_t&, Order&, const size_t&);

Order* removeCompleteOrders(Order*, size_t&);

void saveOrdersInFile(Order*, const size_t&);


#endif //ORDER_HDR
