#include "GameMap.h"

int main()
{
	GameMap map;

	std::string path, start;

	std::cout << "File path> ";
	std::getline(std::cin, path, '\n');
	std::cout << "Starting zone> ";
	std::getline(std::cin, start, '\n');

	if (map.loadDataFromFile(path))
	{
		std::unordered_map<std::string, bool> traverse_results = map.bfs(start);

		map.createDotFile(start + ".dot", traverse_results);
	}
	else
		std::cout << "The file could not be opened.\n";

	return 0;
}