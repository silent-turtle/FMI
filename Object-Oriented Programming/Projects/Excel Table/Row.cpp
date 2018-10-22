#include "Row.h"



Row::Row() :cells(nullptr), cells_size(0), cells_capacity(0)
{
}

Row& Row::operator=(const Row& other)
{
	if (this != &other)
	{
		cells_size = other.cells_size;
		cells_capacity = other.cells_capacity;

		delete[] cells;

		cells = new Cell*[cells_capacity];
		for (size_t i = 0; i < cells_capacity; ++i)
			cells[i] = other.cells[i];

		for (size_t i = 0; i < cells_size; ++i)
			other.cells[i] = nullptr;
	}
	return *this;
}


Row::~Row()
{
	clear();
}


void Row::serialise(std::ofstream& ofs)
{
	for (size_t i = 0; i < cells_size; ++i)
	{
		if (cells[i] != nullptr)
			cells[i]->serialise(ofs);
		if (i != cells_size - 1) ofs << ", ";
	}
}

void Row::deserialise(std::ifstream& ifs)
{
	for (size_t i = 0; i < cells_size; ++i)
	{
		char* content = createStr(ifs);
		if (content != nullptr)
		{
			size_t size = strlen(content);

			Type type_id = getType(content, size);
			const char* type = setType(type_id);

			try
			{
				cells[i] = CellFactory::createCell(type, content);
			}
			catch (std::bad_alloc&)
			{
				throw i;
			}
			catch (const char* msg)
			{
				throw i;
			}

			if(content) delete[] content;
		}
	}
}

void Row::print(size_t* max_lengths, size_t size) const
{
	for (size_t i = 0; i < size; ++i)
	{
		size_t max_length;

		//in case the table is empty
		if (max_lengths == nullptr)
			max_length = 0;
		else max_length = max_lengths[i];

		std::cout << std::setfill(' ') << std::setw(max_length);

		//in case the cell is empty
		if (cells[i] != nullptr)
			cells[i]->viewContent();
		else std::cout << ' ';

		std::cout << " | ";
	}
}

void Row::edit(const char* source, size_t col)
{
	if (col > cells_size)
	{
		std::cout << "The cell doesn't exist!\n";
		return;
	}
	size_t size = strlen(source);

	Type type_id = getType(source, size);
	const char* type = setType(type_id);

	Cell* temp = CellFactory::createCell(type, source);

	if (!temp)
	{
		std::cout << "Invalid data!\n\n";
		return;
	}

	if (cells[col - 1]) delete cells[col - 1];
	cells[col - 1] = temp;
}

const Cell* Row::operator[](size_t col) const
{
	return cells[col - 1];
}

Cell* Row::operator[](size_t col)
{
	return cells[col - 1];
}

void Row::addCell()
{
	if (cells_size >= cells_capacity)
		resize();

	++cells_size;
}

//function that fixes the number of rows and cells
//before loading a table from a file
void Row::setSize(std::ifstream& ifs)
{
	char c;
	size_t cnt = 0;

	do
	{
		if (ifs)
		{
			ifs.get(c);
			if (c == ',')
				++cells_size;
			++cnt;
		}
	} while (c != '\n' && !ifs.eof());

	if (cnt > 1) ++cells_size;

	cells_capacity = cells_size;

	cells = new Cell*[cells_capacity];

	for (size_t i = 0; i < cells_size; ++i)
		cells[i] = nullptr;
}

void Row::clear()
{
	for (size_t i = 0; i < cells_size; ++i)
		delete[] cells[i];

	delete[] cells;
	cells_size = 0;
	cells_capacity = 0;
}

//function that takes as an argument the biggest 
//number of cells in a row and fills each row with 
//nullptr until all rows have the same number of editable cells
void Row::fillRow(size_t size)
{
	if (cells_capacity == 0)
	{
		cells_capacity = 1;
		resize();
	}
	if (size >= cells_capacity)
	{
		cells_capacity = size;
		resize();
		cells_size = size;
	}
}

void Row::resize()
{
	cells_capacity *= 2;

	Cell** temp = new Cell*[cells_capacity];

	for (size_t i = 0; i < cells_size; ++i)
		temp[i] = cells[i];

	for (size_t i = cells_size; i < cells_capacity; ++i)
		temp[i] = nullptr;

	delete[] cells;

	cells = temp;
}

char* Row::createStr(std::ifstream& ifs)
{
	char buffer[1024];
	char c;
	ifs.get(c);
	if (c != '\n') ifs.putback(c);

	size_t cnt = 0;

	do
	{
		if (ifs)
		{
			ifs.get(c);

			if (c == ',' || c == '\n')
			{
				buffer[cnt] = '\0';
				break;
			}
			buffer[cnt] = c;
			++cnt;
		}
	} while (!ifs.eof());

	if (ifs.eof()) buffer[cnt - 1] = '\0';

	size_t space_cnt_beg = 0, space_cnt_end = 0;

	removeWhitespace(buffer, space_cnt_beg, space_cnt_end);
	
	char* newMem;
	if (onlyWhitespace(buffer)) newMem = nullptr;
	else
	{
		newMem = new char[cnt - space_cnt_beg - space_cnt_end + 1];

		strncpy_s(newMem, cnt - space_cnt_beg - space_cnt_end + 1,
			buffer + space_cnt_beg, cnt - space_cnt_beg - space_cnt_end);
	}
	return newMem;
}

Type Row::getType(const char* str, size_t size)
{
	if (str[0] == '\"' && str[size - 1] == '\"')
		return Text;

	size_t cnt = 0, dots_cnt = 0;

	while (str[cnt] != '\0')
	{
		if (!isNumber(str[cnt]) && str[cnt] != '.')
			if (str[0] != '+' && str[0] != '-' || str[0] == '\0')
				throw "Unknown type!";

		if (str[cnt] == ' ')
			throw str[cnt - 1];

		if (str[cnt] == '.') ++dots_cnt;
		++cnt;
	}

	if (!dots_cnt)
		return Integer;

	if (dots_cnt == 1)
		return Double;

	if (dots_cnt == 2)
		return Date;
	if (dots_cnt > 2)
		throw "Unknown type!";
}

bool Row::isNumber(char c)
{
	return (c >= '0' && c <= '9');
}

const char* Row::setType(Type id)
{
	if (id == Integer)
		return "Integer";
	else
		if (id == Double)
			return "Double";
		else
			if (id == Text)
				return "Text";
			else
				if (id == Date)
					return "Date";
				else
					return "Null";
}

void Row::removeWhitespace(char* str, size_t& beg, size_t& end)
{
	size_t size = strlen(str);
	while (str[beg] == ' ')
		++beg;

	while (str[--size] == ' ')
		++end;
}

bool Row::onlyWhitespace(const char* str)
{
	size_t size = strlen(str);

	for (size_t i = 0; i < size; ++i)
		if (str[i] != ' ')
			return false;
	
	return true;
}

//void Row::setCells(Cell** other)
//{
//	if (cells) delete[] cells;
//	cells = new Cell*[cells_capacity];
//	for (size_t i = 0; i < cells_size; ++i)
//		cells[i] = other[i];
//}

//void Row::createCell(const char* content, Cell* c)
//{
//	size_t size = strlen(content);
//
//	Type type_id = getType(content, size);
//	const char* type = setType(type_id);
//
//	try //could be better
//	{
//		c = CellFactory::createCell(type, content);
//	}
//	catch (std::bad_alloc&)
//	{
//		throw pos;
//	}
//	catch (const char* msg)
//	{
//		throw pos;
//	}
//}