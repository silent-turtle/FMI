#ifndef TABLE_HDR
#define TABLE_HDR

#include<fstream>

#include"Row.h"

class Table
{
public:
	Table();
	~Table();

	void menu();


private:
	Row* rows;
	size_t rows_size;
	size_t rows_capacity;

private:
	void serialise(const char* path);
	void deserialise(const char* path);
	void print() const;
	void edit(const char* source, size_t row, size_t col);
	void addRow();
	void addCollumn();
	void help() const;


private:
	Row& operator[](size_t row);
	const Row& operator[](size_t row) const;
	void operator++();
	void operator+();


private:
	void fillTable();
	void clear();
	void setSize(const char*);
	void resize();
	size_t getMaxCellsSize() const;
	size_t* getMaxCellLengths(size_t size) const;
	size_t getMaxColLength(size_t index) const;
};

#endif // TABLE_HDR
