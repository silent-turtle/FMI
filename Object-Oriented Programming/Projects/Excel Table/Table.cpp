#include "Table.h"

const size_t MAX_CMD_SIZE = 7;
const size_t MAX_PATH_SIZE = 128;
const size_t MAX_CONTENT_SIZE = 256;

Table::Table() : rows(nullptr), rows_size(0), rows_capacity(0)
{
}


Table::~Table()
{
	clear();
}

void Table::menu()
{
	char command[MAX_CMD_SIZE];

	help();
	std::cout << "For help, type \"help\"\n\n";

	do
	{
		std::cout << '>';

		std::cin >> std::setw(MAX_CMD_SIZE) >> command;

		if (!strcmp(command, "load"))
		{
			char path[MAX_PATH_SIZE];

			std::cin >> std::setw(MAX_PATH_SIZE) >> path;

			clear();
			setSize(path);
			deserialise(path);
			fillTable();
		}

		else if (!strcmp(command, "save"))
		{
			char path[MAX_PATH_SIZE];

			std::cin >> std::setw(MAX_PATH_SIZE) >> path;

			serialise(path);
		}

		else if (!strcmp(command, "print"))
			print();


		else if (!strcmp(command, "edit"))
		{
			size_t row, col;
			std::cin >> row >> col;

			char content[MAX_CONTENT_SIZE];

			std::cin >> std::setw(MAX_CONTENT_SIZE) >> content;

			if (row > rows_size)
			{
				std::cout << "The cell doesn't exist!\n";

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.clear();

				continue;
			}

			rows[row - 1].edit(content, col);
		}

		else if (!strcmp(command, "addRow"))
			addRow();


		else if (!strcmp(command, "addCol"))
		{
			if (rows_size == 0)
				std::cout << "Cannot do that!";

			addCollumn();
		}
		else if (!strcmp(command, "help"))
			help();

		else if (!strcmp(command, "quit"))
			continue;

		else
			std::cout << "Unknown command!\n\n";

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();

		std::cout << std::endl;
	} while (strcmp(command, "quit"));
}

void Table::serialise(const char* path)
{
	std::ofstream ofs(path);
	if (!ofs.is_open())
	{
		std::cout << "File could not be opened!\n";
		return;
	}

	for (size_t i = 0; i < rows_size; ++i)
	{
		rows[i].serialise(ofs);
		if (i != rows_size - 1) ofs << '\n';
	}

	ofs.close();
}

void Table::deserialise(const char* path)
{
	std::ifstream ifs(path);
	if (!ifs.is_open())
	{
		std::cout << "File could not be opened!\n"; //add exception?
		return;
	}


	for (size_t i = 0; i < rows_size; ++i)
	{
		try
		{
			rows[i].deserialise(ifs);
		}
		catch (size_t col)
		{
			std::cout << "Error: cell [" << i + 1 << ", " << col + 1 << "] is of an unknown data type.\n\n";
			clear();
			break;
		}
		catch (char c)
		{
			std::cout << "Error: Missing a comma after " << c << "\n\n";
			clear();
			break;
		}
	}

	ifs.close();
}

void Table::print() const
{
	if (!rows_size)
	{
		std::cout << "You haven't loaded a table!\n";
		return;
	}
	size_t size = getMaxCellsSize();
	size_t* max_lengths = getMaxCellLengths(size);

	for (size_t i = 0; i < rows_size; ++i)
	{
		rows[i].print(max_lengths, size);
		std::cout << std::endl;
	}

	delete[] max_lengths;
}

void Table::edit(const char* source, size_t row, size_t col)
{
	if (row >= rows_size || col >= rows[row - 1].getCellsSize())
	{
		std::cout << "Cell [" << row << ", " << col << "] doesn't exist!\n\n";
		return;
	}

	try
	{
		rows[row - 1].edit(source, col);
	}
	catch (const char* msg)
	{
		std::cout << "Could not edit the cell at row " << row
			<< ", col " << col << ". " << source << msg << "\n\n";
	}
	catch (std::bad_alloc&)
	{
		std::cout << "Could not edit the cell at row " << row
			<< ", col " << col << "!\n\n";
	}
}

void Table::help() const
{
	std::cout << "\nWelcome! This is a list of available commands:\n"
		<< "1. load <pathfile> - load a table from a file;\n"
		<< "2. save <pathfile> - save a table to a file;\n"
		<< "3. edit <row number> <collumn number> <content> - edit a specific cell;\n"
		<< "4. print - print the table'\n"
		<< "5. quit - quit the program.\n\n";
}

void Table::addRow()
{
	if (rows_capacity == 0)
	{
		rows_capacity = 2;
		resize();
	}

	if (rows_size >= rows_capacity)
		resize();

	size_t max_cell_size = getMaxCellsSize();
	rows[rows_size].fillRow(max_cell_size);

	++rows_size;
}

void Table::addCollumn()
{
	for (size_t i = 0; i < rows_size; ++i)
		rows[i].addCell();
}

Row& Table::operator[](size_t row)
{
	return rows[row - 1];
}

const Row& Table::operator[](size_t row) const
{
	return rows[row - 1];
}

void Table::operator++()
{
	addRow();
}

void Table::operator+()
{
	addCollumn();
}

void Table::fillTable()
{
	size_t max_cell_size = getMaxCellsSize();

	for (size_t i = 0; i < rows_size; ++i)
	{
		rows[i].fillRow(max_cell_size);
	}
}

void Table::clear()
{
	delete[] rows;
	rows = nullptr;
	rows_size = 0;
	rows_capacity = 0;
}

void Table::setSize(const char* path)
{
	std::ifstream ifs(path);
	if (!ifs.is_open())
	{
		rows_size = 0;
		return;
	}

	char c;

	while (!ifs.eof())
	{
		if (ifs)
		{
			ifs.get(c);
			if (c == '\n')
				++rows_size;
		}
	}

	++rows_size;
	rows_capacity = rows_size;

	rows = new Row[rows_capacity];

	ifs.clear();
	ifs.seekg(0, std::ios::beg);

	for (size_t i = 0; i < rows_size; ++i)
		rows[i].setSize(ifs);

	ifs.close();
}

void Table::resize()
{
	rows_capacity *= 2;
	Row* temp = new Row[rows_capacity];

	for (size_t i = 0; i < rows_size; ++i)
		temp[i] = rows[i];

	delete[] rows;

	rows = temp;
}

//function that gets the biggest number of cells in a row
size_t Table::getMaxCellsSize() const
{
	size_t res = 0;
	for (size_t i = 0; i < rows_size; ++i)
	{
		size_t cur = rows[i].getCellsSize();
		if (res < cur) res = cur;
	}
	return res;
}

//function that returns an array of the biggest cell lengths in each collumn
size_t* Table::getMaxCellLengths(size_t size) const
{
	size_t* temp;
	if (size == 0)
		temp = nullptr;
	else
	temp = new size_t[size];
	
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = getMaxColLength(i+1);
	}
	return temp;
}

size_t Table::getMaxColLength(size_t index) const
{
	size_t max = 0;
	for (size_t i = 0; i < rows_size; ++i)
	{
		size_t cur = 0;
		if (rows[i][index] != nullptr)
		{
			//if (index <= rows[i].getCellsSize())
				cur = rows[i][index]->getLength();

			if (cur >= max) max = cur;
		}
	}
	return max;
}