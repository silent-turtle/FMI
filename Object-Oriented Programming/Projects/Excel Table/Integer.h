#ifndef INTEGER_HDR
#define INTEGER_HDR

#include"Cell.h"


class Integer : public Cell
{
public:
	Integer();
	Integer(int num);
	~Integer();

	int getNum() const { return num; }
	void viewContent() const { std::cout << num; }
	void deserialise(std::ifstream& ifs);
	void serialise(std::ofstream& ofs);
	size_t getLength() const;

private:
	int num;
};

#endif //INTEGER_HDR