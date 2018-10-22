#ifndef CELL_FACTORY_HDR
#define CELL_FACTORY_HDR

#include "Cell.h"
#include"Integer.h"
#include"Date.h"
#include"Double.h"
#include"Text.h"

class CellFactory
{
public:

	//the default constructor is private and
	//all methods are static as there's
	//no need for instances of this class
	static Cell* createCell(const char* cmd, const char*);

private:
	static int stringToInt(const char*, size_t&, char = '\0');
	static char* stringToText(const char*);

	CellFactory() { }

};

#endif //CELL_FACTORY_HDR
