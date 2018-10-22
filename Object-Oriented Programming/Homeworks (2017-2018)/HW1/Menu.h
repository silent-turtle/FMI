#ifndef MENU_HDR
#define MENU_HDR

#include"Order.h"

void menu();

void addWallet(Wallet*&, size_t&, Transaction*&, size_t&);

void makeOrder(Order*&, size_t&, Wallet*, const size_t&, Transaction*, size_t&);

void walletInfo(Wallet*, const size_t&, Transaction*, const size_t&);

void swap(Wallet&, Wallet&);

void bubbleSort(Wallet*, const size_t&, Wallet*, const size_t&, Transaction*, const size_t&);

void getTimeOfFirstAndLastOrder(Transaction*, const size_t&, const size_t&, long long&, long long&);

void attractInvestors(Wallet*, const size_t&, Transaction*, const size_t&);

void quit(Wallet*, const size_t&, Transaction*, const size_t&, Order*, const size_t&);

#endif //MENU_HDR
