#include"Menu.h"


void menu()
{
	size_t wallet_count = sizeOfWalletFile();
	size_t transaction_count = sizeOfTransactionFile();
	size_t order_count = sizeOfOrderFile();

	Wallet* walletList = loadWalletList(wallet_count);
	Transaction* transactionList = loadTransactionList(transaction_count);
	Order* orderList = loadOrdersInList(order_count);

	std::cout << "--------------------------------------------------------------------------------\n"
		<< "Welcome to the new non-cryptocurrency system!\n\n"
		<< "You can choose one of the following options:\n"
		<< ">'add-wallet money name'\n"
		<< "- adds a new wallet to the system, the name should be max 255 characters long;\n"
		<< ">'make-order type fmiCoins walletId'\n"
		<< "- creates a new order, type must be BUY/SELL;\n"
		<< ">'wallet-info walletId'\n"
		<< "- gives information about a wallet;\n"
		<< ">'attract-investors'\n"
		<< "- gives the following information about the ten richest clients:\n"
		<< "  -- Client's ID;\n"
		<< "  -- Client's amount of fmiCoins;\n"
		<< "  -- Client's number of complete orders;\n"
		<< "  -- Time of the client's first order;\n"
		<< "  -- Time of the client's last order;\n"
		<< ">'help'\n"
		<< "- opens this message box;\n"
		<< ">'quit'\n"
		<< "- saves all changes and quits the program.\n"
		<< "--------------------------------------------------------------------------------\n";

	do
	{
		char command[MAX_INPUT_SIZE];
		std::cin.getline(command, MAX_INPUT_SIZE);
		strtok(command, " ");

		if (!strcmp(command, "add-wallet"))
		{
			addWallet(walletList, wallet_count, transactionList, transaction_count);
		}
		else if (!strcmp(command, "make-order"))
		{
			makeOrder(orderList, order_count, walletList, wallet_count, transactionList, transaction_count);
		}
		else if (!strcmp(command, "wallet-info"))
			walletInfo(walletList, wallet_count, transactionList, transaction_count);
		else if (!strcmp(command, "attract-investors"))
			attractInvestors(walletList, wallet_count, transactionList, transaction_count);
		else if (!strcmp(command, "quit"))
		{
			std::cout << "Goodbye!";
			quit(walletList, wallet_count, transactionList, transaction_count, orderList, order_count);
			break;
		}
		else if (!strcmp(command, "help"))
		{
			std::cout << "--------------------------------------------------------------------------------\n"
				<< "You can choose one of the following options:\n"
				<< ">'add-wallet money name'\n"
				<< "- adds a new wallet to the system, the name should be max 255 characters long;\n"
				<< ">'make-order type fmiCoins walletId'\n"
				<< "- creates a new order, type must be BUY/SELL;\n"
				<< ">'wallet-info walletId'\n"
				<< "- gives information about a wallet;\n"
				<< ">'attract-investors'\n"
				<< "- gives the following information about the ten richest clients:\n"
				<< "  -- Client's ID;\n"
				<< "  -- Client's amount of fmiCoins;\n"
				<< "  -- Client's number of complete orders;\n"
				<< "  -- Time of the client's first order;\n"
				<< "  -- Time of the client's last order;\n"
				<< ">'help'\n"
				<< "- opens this message box;\n"
				<< ">'quit'\n"
				<< "- saves all changes and quits the program.\n"
				<< "--------------------------------------------------------------------------------\n";
		}
		else std::cout << "Unknown command! Please, try again!\n";

	} while (true);


	delete[] walletList;
	delete[] transactionList;
	delete[] orderList;
}

void addWallet(Wallet*& w, size_t& w_num, Transaction*& t, size_t& t_num)
{
	w = addWalletInList(w, ++w_num);
	double new_wallet_coins = w[w_num - 1].fiatMoney / CURRENCY_NUM;
	t = addTransactionInList(t, ++t_num, SYSTEM_ID, w[w_num - 1].id, new_wallet_coins);
}

void makeOrder(Order*& o, size_t& o_num, Wallet* w, const size_t& w_num, Transaction* t, size_t& t_num)
{
	o = addOrderInList(o, ++o_num, w, w_num, t, t_num);
	o = removeCompleteOrders(o, o_num);
}

void walletInfo(Wallet* w, const size_t& w_num, Transaction* t, const size_t& t_num)
{
	bool idExists = false;
	size_t id;
	char* str = strtok(NULL, "\n");
	id = atoi(str);

	for (size_t i = 0; i < w_num; ++i)
	{
		if (w[i].id == id)
		{
			idExists = true;
			std::cout << "Owner> " << w[i].owner << std::endl;
			std::cout << "Balance> " << w[i].fiatMoney << std::endl;
			double coins = printCoins(t, t_num, id);
			std::cout << "FMICoins> " << coins << std::endl << std::endl;
		}
	}
	if (!idExists) std::cout << "There is no such ID!" << std::endl << std::endl;
}


void swap(Wallet& a, Wallet& b)
{
	Wallet temp = a;
	a = b;
	b = temp;
}

void bubbleSort(Wallet* r_w, const size_t& size, Wallet* w,
	const size_t& w_cnt, Transaction* t, const size_t& t_num)
{
	bool sorted = false;

	do
	{
		sorted = true;
		for (size_t cnt = 0; cnt < size - 1; ++cnt)
		{
			double cur_wallet_coins = printCoins(t, t_num, r_w[cnt].id);
			double next_wallet_coins = printCoins(t, t_num, r_w[cnt + 1].id);
			if (cur_wallet_coins < next_wallet_coins)
			{
				sorted = false;
				swap(r_w[cnt], r_w[cnt + 1]);
			}
		}
	} while (!sorted);
}


void getTimeOfFirstAndLastOrder(Transaction* t, const size_t& t_num, const size_t& id,
	long long& time_of_first_order, long long& time_of_last_order)
{
	for (size_t i = 0; i < t_num; ++i)
	{
		if ((t[i].receiverId == id || t[i].senderId == id) && t[i].timeOfCompletedOrder)
		{
			time_of_first_order = t[i].timeOfCompletedOrder;
			break;
		}
	}

	for (size_t i = t_num; i > 0; --i)
	{
		if ((t[i - 1].receiverId == id || t[i - 1].senderId == id) && t[i - 1].timeOfCompletedOrder)
		{
			time_of_last_order = t[i - 1].timeOfCompletedOrder;
			break;
		}
	}
}

void attractInvestors(Wallet* w, const size_t& w_num, Transaction* t, const size_t& t_num)
{
	Wallet richest_wallets[TOP_LIST_MAX_SIZE];

	size_t size = TOP_LIST_MAX_SIZE;

	if (size > w_num)//if the wallets are less than 10, print all the wallets
	{
		size = w_num;
	}

	size_t cnt = 0;
	while (cnt < size)
	{
		richest_wallets[cnt] = w[cnt];
		++cnt;
	}

	bubbleSort(richest_wallets, size, w, 0, t, t_num);


	//if the wallets are more than 10, compares every next wallet with the one
	//with the smallest ammount of coins in the list
	if (size < w_num)
	{
		while (cnt < w_num)
		{
			double smallest_amount = printCoins(t, t_num, richest_wallets[size - 1].id);
			double next_wallet_coins = printCoins(t, t_num, w[cnt].id);
			if (smallest_amount < next_wallet_coins)
			{
				richest_wallets[size - 1] = w[cnt];
				bubbleSort(richest_wallets, size, w, cnt, t, t_num);
			}
			++cnt;
		}

	}


	for (size_t i = 0; i < size; ++i)
	{
		double coins = printCoins(t, t_num, richest_wallets[i].id);
		long long time_of_first_order = 0, time_of_last_order = 0;

		getTimeOfFirstAndLastOrder(t, t_num, richest_wallets[i].id, time_of_first_order, time_of_last_order);

		std::cout << i + 1 << ". " << richest_wallets[i].id << ' ' << coins << ' ';

		if (!richest_wallets[i].completeOrders)
			std::cout << "no completed orders\n";
		else std::cout << richest_wallets[i].completeOrders << ' ' <<
			time_of_first_order << ' ' << time_of_last_order << std::endl;
	}
}

void quit(Wallet* w, const size_t& w_num, Transaction* t, 
	const size_t& t_num, Order* o, const size_t& o_num)
{
	saveWalletsInFile(w, w_num);
	saveTransactionsInFile(t, t_num);
	saveOrdersInFile(o, o_num);
}