#include "Conga.h"

#include<iomanip>

const short MAX_COMMAND_SIZE = 12;
const short MAX_NAME_SIZE = 256;
const short MAX_UNI_SIZE = 5;

Conga::Conga() : cl(nullptr), size(1), capacity(2)
{
	cl = new CongaLine*[capacity];

	for (size_t i = 0; i < size; ++i)
		cl[i] = new CongaLine();

	for (size_t i = size; i < capacity; ++i)
		cl[i] = nullptr;
}


Conga::~Conga()
{
	clean();
}

void Conga::menu()
{
	help();

	char command[MAX_COMMAND_SIZE];
	do
	{
		try
		{
			std::cout << "\n>";
			std::cin >> std::setw(MAX_COMMAND_SIZE) >> command;

			if (!strcmp(command, "append"))
			{
				char name[MAX_NAME_SIZE];
				char uni[MAX_UNI_SIZE];
				size_t idx;

				std::cin >> std::setw(MAX_NAME_SIZE) >> name;
				std::cin >> std::setw(MAX_UNI_SIZE) >> uni;
				std::cin >> idx;

				append(name, uni, idx);
			}
			else if (!strcmp(command, "removeLast"))
			{
				size_t idx;
				std::cin >> idx;

				removeAtLast(idx);
			}
			else if (!strcmp(command, "removeFirst"))
			{
				size_t idx;
				std::cin >> idx;

				removeAtFirst(idx);
			}
			else if (!strcmp(command, "remove"))
			{
				char name[MAX_NAME_SIZE];
				size_t idx;

				std::cin >> std::setw(MAX_NAME_SIZE) >> name;
				std::cin >> idx;

				remove(name, idx);
			}
			else if (!strcmp(command, "merge"))
			{
				size_t idx1, idx2;
				std::cin >> idx1 >> idx2;

				merge(idx1, idx2);
			}
			else if (!strcmp(command, "print"))
				print();
			else if (!strcmp(command, "help"))
				help();
			else
			{
				if(strcmp(command, "quit"))
				std::cout << "Unknown command!\n\n";
				
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
	} while (strcmp(command, "quit"));
}

void Conga::append(const char * name, const char * uni, size_t idx)
{
	if (idx >= size)
		throw std::out_of_range("A line with this index doesn't exist.");

	cl[idx]->append(name, uni);
}

void Conga::removeAtFirst(size_t idx)
{
	if (idx >= size)
		throw std::out_of_range("A line with this index doesn't exist.");

	cl[idx]->removeAtFirst();

	if (cl[idx]->begin().getPtr() == nullptr)
	{
		swap(cl[idx], cl[size - 1]);
		--size;
	}
}

void Conga::removeAtLast(size_t idx)
{
	if (idx >= size)
		throw std::out_of_range("A line with this index doesn't exist.");

	cl[idx]->removeAtLast();

	if (cl[idx]->begin().getPtr() == nullptr)
	{
		swap(cl[idx], cl[size - 1]);
		--size;
	}
}

void Conga::remove(const char* name, size_t idx)
{
	if (idx >= size)
		throw std::out_of_range("A line with this index doesn't exist.");


	if (!strcmp(name, cl[idx]->begin().getName()))
	{
		removeAtFirst(idx);
		return;
	}

	if (cl[idx]->getTailName())
		if (!strcmp(name, cl[idx]->getTailName()))
		{
			removeAtLast(idx);
			return;
		}

	CongaLine::Iterator it = cl[idx]->find(name);
	CongaLine::Iterator next = it;
	++next;

	cl[idx]->remove(it);

	if (size >= capacity)
		resize(2 * capacity);

	cl[size] = new CongaLine();
	cl[size]->append(next);
	++size;
}

void Conga::merge(size_t idx1, size_t idx2)
{
	if (idx1 >= size || idx2 >= size)
		throw std::out_of_range("A line with this index doesn't exist.");

	cl[idx1]->append(cl[idx2]->begin());
	cl[idx2] = nullptr;

	if (idx1 > idx2)
		swap(cl[idx1], cl[idx2]);

	swap(cl[idx2], cl[size - 1]);
	--size;
}

void Conga::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "Line" << i << ": ";
		cl[i]->print();
		std::cout << std::endl;
	}
}

void Conga::help() const
{
	std::cout << "What would you like to do?\n"
		<< "1> append <name> <uni> <lineindex>;\n"
		<< "2> removeLast <lineindex>;\n"
		<< "3> removeFirst <lineindex>;\n"
		<< "4> remove <name> <lineindex>;\n"
		<< "5> merge <lineindex1> <lineindex2>;\n"
		<< "6> print;\n"
		<< "8> help;\n"
		<< "9> quit.\n";
}

void Conga::resize(size_t newSize)
{
	CongaLine** temp = new CongaLine*[newSize];

	size_t temp_size;

	(newSize > size) ? temp_size = size : temp_size = newSize;

	for (size_t i = 0; i < temp_size; ++i)
		temp[i] = cl[i];

	for (size_t i = temp_size; i < newSize; ++i)
		temp[i] = nullptr;

	delete[] cl;
	cl = nullptr;
	cl = temp;

	capacity = newSize;
}

void Conga::clean()
{
	for (size_t i = 0; i < size; ++i)
		delete cl[i];

	delete[] cl;

	size = 0;
	capacity = 0;
}

void Conga::swap(CongaLine* cl1, CongaLine* cl2)
{
	CongaLine* temp = cl1;
	cl1 = cl2;
	cl2 = temp;
}
