#include"Order.h"

size_t sizeOfOrderFile()
{
	std::ifstream ifs;
	ifs.open("orders.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return 0;
	}

	ifs.seekg(0, std::ios::end);
	size_t num = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	ifs.close();

	size_t cnt = num / sizeof(Order);

	return cnt;
}

Order* loadOrdersInList(size_t& num)
{
	Order* o = new(std::nothrow) Order[num];
	if (!o)
	{
		return NULL;
	}

	std::ifstream ifs;
	ifs.open("orders.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return NULL;
	}

	for (size_t i = 0; i < num; ++i)
	{
		ifs.read((char*)&o[i].type, sizeof(o[i].type));
		ifs.read((char*)&o[i].walletId, sizeof(size_t));
		ifs.read((char*)&o[i].fmiCoins, sizeof(double));
	}

	ifs.close();

	return o;
}

Order::Type typeValue(char* str)
{
	if (!strcmp(str, "SELL"))
		return Order::SELL;

	else if (!strcmp(str, "BUY"))
		return Order::BUY;
}

void readToFile(const char* Path, char sender_name[], char receiver_name[], double coins,
	size_t t_cnt, double coin_cnt, bool flag)
{
	std::ofstream ofs;
	ofs.open(Path, std::ios::app);
	if (!ofs.is_open())
	{
		std::cout << "The file could not be opened!";
		return;
	}

	if (!flag)//if the order hasn't been finished yet
		ofs << sender_name << ' ' << receiver_name << ' ' << coins << std::endl;
	else
		ofs << t_cnt << ' ' << coin_cnt;

	ofs.close();
}

Order* addOrderInList(Order* o, size_t& o_num, Wallet* w, const size_t& w_num, Transaction*& t, size_t& t_num)
{
	Order* newMem = new(std::nothrow) Order[o_num];
	if (!newMem)
	{
		return NULL;
	}

	for (size_t i = 0; i < o_num - 1; ++i)
	{
		newMem[i].type = o[i].type;
		newMem[i].walletId = o[i].walletId;
		newMem[i].fmiCoins = o[i].fmiCoins;
	}

	if (addNewOrder(newMem[o_num - 1], w, w_num, t, t_num))
	{
		//this is information for the text file
		size_t transactions_cnt = 0;
		double total_coins = 0;
		long long order_time = time(0);
		bool orderIsDone = false;//if it's false it keeps adding new transactions to the file
		                         //else adds the total number of transactions and the coins in money

		for (size_t i = 0; newMem[o_num - 1].fmiCoins && i < o_num - 1; ++i)
		{
			//if the orders are of different type and the ids are different
			if (newMem[i].type != newMem[o_num - 1].type &&
				newMem[i].walletId != newMem[o_num - 1].walletId)
			{
				size_t time_num_cnt = numCnt(order_time);
				size_t id_num_cnt = numCnt(newMem[o_num - 1].walletId);

				//creates a name for the text file
				char filename[MAX_PATH_NAME_SIZE];
				createPathStr(filename, order_time, time_num_cnt, newMem[o_num - 1].walletId, id_num_cnt);

				double coins_to_transfer;
				if (newMem[i].fmiCoins > newMem[o_num - 1].fmiCoins)
				{
					coins_to_transfer = newMem[o_num - 1].fmiCoins;
				}
				coins_to_transfer = newMem[i].fmiCoins;

				newMem[o_num - 1].fmiCoins -= coins_to_transfer;
				newMem[i].fmiCoins -= coins_to_transfer;

				if (newMem[o_num - 1].type == 0)//if the order is SELL
				{
					t = addTransactionInList(t, ++t_num, newMem[o_num - 1].walletId,
						newMem[i].walletId, coins_to_transfer);

					++transactions_cnt;
					total_coins += coins_to_transfer;

					w[newMem[o_num - 1].walletId - 1].fiatMoney += coins_to_transfer * CURRENCY_NUM;
					w[newMem[i].walletId - 1].fiatMoney -= coins_to_transfer * CURRENCY_NUM;
					readToFile(filename, w[newMem[o_num - 1].walletId - 1].owner, w[newMem[i].walletId - 1].owner,
						coins_to_transfer, transactions_cnt, total_coins, orderIsDone);
				}
				else //if the order is BUY
				{
					t = addTransactionInList(t, ++t_num, newMem[i].walletId,
						newMem[o_num - 1].walletId, coins_to_transfer);

					++transactions_cnt;
					total_coins += coins_to_transfer;

					w[newMem[o_num - 1].walletId - 1].fiatMoney -= coins_to_transfer * CURRENCY_NUM;
					w[newMem[i].walletId - 1].fiatMoney += coins_to_transfer * CURRENCY_NUM;
					readToFile(filename, w[newMem[i].walletId - 1].owner, w[newMem[o_num - 1].walletId].owner,
						coins_to_transfer, transactions_cnt, total_coins, orderIsDone);
				}


				//if this is the last order before the current one or if there are no more coins in the current one
				if (i == (o_num - 2) || newMem[o_num - 1].fmiCoins == 0)
				{
					if (newMem[i].fmiCoins)
						moveUnfinishedOrder(newMem, o_num, newMem[i], i);
					
					orderIsDone = true;
					t[t_num - 1].timeOfCompletedOrder = time(0);

					if(newMem[o_num - 1].fmiCoins == 0) //if this is true, the current order is completed
					++w[newMem[o_num - 1].walletId - 1].completeOrders;

					total_coins *= CURRENCY_NUM;//changes the coins into money
					readToFile(filename, w[newMem[i].walletId - 1].owner, w[newMem[o_num - 1].walletId].owner,
						coins_to_transfer, transactions_cnt, total_coins, orderIsDone);
					break;
				}
			}
		}

		delete[]o;
		o = newMem;
	}
	else //if there's no new order it 
	{
		delete[]newMem;
		--o_num;
	}

	return o;
}


bool addNewOrder(Order& o, Wallet* w, const size_t& w_num, Transaction* t, const size_t& t_num)
{
	size_t id;
	double coins;

	char* str = strtok(NULL, " ");
	o.type = (Order::Type)typeValue(str);

	str = strtok(NULL, " ");
	coins = atof(str);

	str = strtok(NULL, "\n");
	id = atoi(str);
	double id_coins = printCoins(t, t_num, id);

	if (id > w_num)
	{
		std::cout << "There's no such ID!\n";
		return false;
	}
	if (id != w[id - 1].id)
	{
		std::cout << "There's no such ID!\n";
		return false;
	}
	if (!o.type)//SELL
	{
		if (coins > id_coins)
		{
			std::cout << "Insufficient ammount of fmiCoins!\n";
			return false;
		}
	}
	else//BUY
	{
		double coins_in_money = coins * CURRENCY_NUM;
		if (coins_in_money > w[id - 1].fiatMoney)
		{
			std::cout << "Insufficient ammount of money in the wallet!\n";
			return false;
		}
	}

	o.walletId = id;
	o.fmiCoins = coins;
	return true;
}

size_t numCnt(long long num)
{
	size_t cnt = 0;
	while (num)
	{
		++cnt;
		num /= 10;
	}
	return cnt;
}


void createPathStr(char str[], long long time, const size_t& time_size, size_t id, const size_t& id_size)
{
	for (size_t i = id_size - 1; id && i >= 0; --i)
	{
		str[i] = (id % 10) + '0';
		id /= 10;
	}

	str[id_size] = ' ';

	size_t size = id_size + 1 + time_size;

	for (size_t i = size - 1; time && i >= id_size + 1; --i)
	{
		str[i] = (time % 10) + '0';
		time /= 10;
	}

	str[size] = '.';
	str[size + 1] = 't';
	str[size + 2] = 'x';
	str[size + 3] = 't';
	str[size + 4] = '\0';
}

void moveUnfinishedOrder(Order* o, const size_t& о_num, Order& order, const size_t& index)
{
	for (size_t i = index; i < о_num - 1; ++i)
	{
		o[i].type = o[i + 1].type;
		o[i].walletId = o[i + 1].walletId;
		o[i].fmiCoins = o[i + 1].fmiCoins;
	}
	o[о_num - 1].type = order.type;
	o[о_num - 1].walletId = order.walletId;
	o[о_num - 1].fmiCoins = order.fmiCoins;
}

Order* removeCompleteOrders(Order* o, size_t& o_num)
{
	size_t cnt = 0;
	for (size_t i = 0; i < o_num; ++i)
	{
		if (o[i].fmiCoins)
			++cnt;
	}
	if (cnt)
	{
		Order* newMem = new(std::nothrow) Order[cnt];
		if (!newMem)
		{
			return NULL;
		}

		for (size_t i = 0; i < cnt; ++i)
		{
			for (size_t j = 0; j < o_num; ++j)
			{
				if (o[j].fmiCoins)
				{
					newMem[i].type = o[j].type;
					newMem[i].walletId = o[j].walletId;
					newMem[i].fmiCoins = o[j].fmiCoins;
					++i;
				}
			}
		}

		o_num = cnt;

		delete[]o;
		o = newMem;
	}
	else delete[]o;
	return o;
}

void saveOrdersInFile(Order* o, const size_t& o_num)
{
	std::ofstream ofs;
	ofs.open("orders.dat", std::ios::binary | std::ios::trunc);
	if (!ofs.is_open())
	{
		std::cout << "The file 'orders.dat' could not be opened!";
		return;
	}

	for (size_t i = 0; i < o_num; ++i)
	{
		ofs.write((const char*)&o[i].type, sizeof(o[i].type));
		ofs.write((const char*)&o[i].walletId, sizeof(size_t));
		ofs.write((const char*)&o[i].fmiCoins, sizeof(double));
	}

	ofs.close();
}