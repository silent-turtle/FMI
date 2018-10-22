#include "MessageCollection.h"



MessageCollection::MessageCollection() : msg(nullptr), msg_size(0)
{
}

MessageCollection::MessageCollection(const MessageCollection & other)
{
	if (this != &other)
	{
		msg_size = other.msg_size;

		msg = new Message[msg_size];

		for (size_t i = 0; i < msg_size; ++i)
		{
			msg[i] = other.msg[i];
		}
	}
}


MessageCollection::~MessageCollection()
{
	delete[] msg;
}

void MessageCollection::setMessages(const char* path)
{
	std::ifstream ifs;
	ifs.open(path, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "File could not be opened!\n";
		return;
	}

	setSize(path, ifs);

	ifs.seekg(0, std::ios::beg);

	deserialise(path, ifs);

	ifs.close();
}

void MessageCollection::setSize(const char* path, std::ifstream& ifs)
{
	/*std::ifstream ifs(path, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "Could not open the file!\n";
		return;
	}*/
	size_t cnt = 0;
	while (!ifs.eof())
	{
		if (ifs)
		{
			++cnt;
			char c;
			ifs.get(c);
			if (c == '\n')
				++msg_size;
		}
	}

	if (cnt) ++msg_size;

	//ifs.close();

	ifs.clear();

	if (msg) delete[] msg;

	msg = new Message[msg_size];
}

void MessageCollection::deserialise(const char* path, std::ifstream& ifs)
{
	//std::ifstream ifs(path, std::ios::in);
	//if (!ifs.is_open())
	//{
	//	std::cout << "Could not open the file!\n";
	//	return;
	//}

	for (size_t i = 0; i < msg_size; ++i)
	{
		size_t cnt = 0;
		char c;
		char buff[280];

		do
		{
			if (ifs)
			{
				ifs.get(c);

				if (c == '\n')
				{
					buff[cnt] = '\0';
					break;
				}

				buff[cnt] = c;
				++cnt;
			}
		} while (!ifs.eof());

		if (ifs.eof()) buff[cnt - 1] = '\0';

		msg[i].setContent(buff);
	}

	//ifs.close();
}

CompareVal* MessageCollection::compare(const char * str)
{
	CompareVal* newMem = new CompareVal[msg_size];
	for (size_t i = 0; i < msg_size; ++i)
	{
		newMem[i].val = msg[i].compare(str);
		newMem[i].pos = i;
	}
	return newMem;
}


void MessageCollection::printCompare(const char* str)
{
	CompareVal* cv = compare(str);
	
	bubbleSort(cv);

	for (size_t i = 0; i < msg_size; ++i)
		std::cout << msg[cv[i].pos].getLine() << std::endl;

	delete[] cv;
}

void MessageCollection::printHashtags() const
{
	for (size_t i = 0; i < msg_size; ++i)
		msg[i].printHashtags();
}


MessageCollection& MessageCollection::operator+=(const char * str)
{
	try 
	{
	addMessage(str);
	}
	catch (std::bad_alloc&)
	{	
		std::cout << "Could not add a new message!\n";
	}

	return *this;
}

MessageCollection MessageCollection::operator+(const char* str)
{
	try 
	{
	MessageCollection temp(*this);
	
 	temp.addMessage(str);
	
	return temp;
	}
	catch (std::bad_alloc&)
	{
		std::cout << "Could not add a new message!\n";
		return *this;
	};
}

const char* MessageCollection::operator[](const char* str)
{
	CompareVal* temp = compare(str);

	size_t max = temp[0].val, pos = temp[0].pos;
	for (size_t i = 1; i < msg_size; ++i)
	{
		if (temp[i].val > max)
		{
			max = temp[i].val;
			pos = temp[i].pos;
		}
	}

	delete[] temp;

	return msg[pos].getLine();
}


void MessageCollection::swap(CompareVal& a, CompareVal& b)
{
	CompareVal temp = a;

	a = b;

	b = temp;
}

void MessageCollection::bubbleSort(CompareVal* cv)
{
	bool isSort = false;

	do
	{
		isSort = true;

		for (size_t i = 0; i < msg_size - 1; ++i)
		{
			if (cv[i].val < cv[i + 1].val)
			{
				isSort = false;
				swap(cv[i], cv[i + 1]);
			}
		}
	} while (!isSort);
}

void MessageCollection::addMessage(const char* str)
{
	Message* newMem = new Message[msg_size + 1];

	for (size_t i = 0; i < msg_size; ++i)
	{
		try
		{
		newMem[i] = msg[i];
		}
		catch (std::bad_alloc&)
		{
			delete[] newMem;
			throw;
		}
	}

	newMem[msg_size].setContent(str);

	if (msg) delete[] msg;

	msg = newMem;
	++msg_size;
}
