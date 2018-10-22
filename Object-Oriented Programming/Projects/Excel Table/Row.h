#ifndef ROW_HDR
#define ROW_HDR

#include<iomanip>

#include"Cell.h"
#include"CellFactory.h"

enum Type
{
	Integer,
	Double,
	Text,
	Date
};

class Row
{
public:
	Row();
	Row& operator=(const Row& other);
	~Row();

public:
	void serialise(std::ofstream&);
	void deserialise(std::ifstream&);
	void print(size_t* max_lengths, size_t size) const;
	void edit(const char* source, size_t col);

public:
	const Cell* operator[](size_t col) const;
	Cell* operator[](size_t col);

public:
	size_t getCellsSize() const { return cells_size; }
	void addCell();
	void setSize(std::ifstream&);
	void clear();
	void fillRow(size_t size);

private:
	Cell** cells;
	size_t cells_size;
	size_t cells_capacity;

private:
	//void setCells(Cell** other);
	void resize();
	//void createCell(const char* content, Cell* c);
	char* createStr(std::ifstream&);
	Type getType(const char* str, size_t size);
	bool isNumber(char);
	const char* setType(Type);
	void removeWhitespace(char* str, size_t& beg, size_t& end);
	bool onlyWhitespace(const char*);
};

#endif //ROW_HDR
