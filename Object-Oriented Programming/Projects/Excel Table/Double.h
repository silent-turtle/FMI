#ifndef DOUBLE_HDR
#define DOUBLE_HDR

#include"Cell.h"

class Double : public Cell
{
public:
	Double(double num, size_t length);
	~Double();

	void viewContent() const { std::cout << num; }

	void deserialise(std::ifstream& ifs);
	void serialise(std::ofstream& ofs);
	size_t getLength() const { return num_length; }

private:
	double num;
	size_t num_length;
};

#endif //DOUBLE_HDR
