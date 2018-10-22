#ifndef DATE_HDR
#define DATE_HDR

#include<iomanip>

#include"Cell.h"

class Date : public Cell
{
public:
	//Date();
	Date(size_t d, size_t m, size_t y);
	~Date();


	void viewContent() const { std::cout << std::setfill('0') << 
		std::setw(2) << day << "." << std::setw(2) << month << "." << year; }
	void deserialise(std::ifstream& ifs);
	void serialise(std::ofstream& ofs);
	size_t getLength() const;

private:
	size_t day, month, year;


};

#endif //DATE_HDR
