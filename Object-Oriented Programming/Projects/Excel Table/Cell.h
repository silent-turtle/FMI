#ifndef CELL_HDR
#define CELL_HDR

#include<iostream>
#include<fstream>


class Cell
{
public:
	Cell();
	Cell& operator=(const Cell&) = delete;
	Cell(const Cell&) = delete;
	virtual ~Cell();

	
	virtual void viewContent() const = 0;
	virtual size_t getLength() const = 0;
	virtual void deserialise(std::ifstream& ifs) = 0;
	virtual void serialise(std::ofstream& ofs) = 0;
};

#endif // CELL_HDR
