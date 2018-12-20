#include"FolkDance.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
		std::cout << "There's no filepath!\n";

	FolkDance fd;
	fd.menu(argv[1]);

	return 0;
}