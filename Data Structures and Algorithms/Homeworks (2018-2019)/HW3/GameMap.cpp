#include "GameMap.h"


bool GameMap::loadDataFromFile(const std::string& path)
{
	std::ifstream ifs(path);

	if (!ifs.is_open())
		return false;

	std::string buffer;

	std::getline(ifs, buffer);

	while (!ifs.eof())
	{
		std::getline(ifs, buffer);
		if (buffer == "")
			continue;

		if (buffer == "[keys]")
			break;

		size_t beg = 0, end = 0;

		while (buffer[end] != '-')
			++end;
		--end;

		std::string zone = buffer.substr(beg, end - beg);

		//skips " -> "
		end += 4;

		beg = end;

		while (buffer[end] != '[' && buffer[end] != ';')
			++end;

		if (buffer[end] == '[')
			--end;

		std::string adjacent_zone = buffer.substr(beg, end - beg);

		std::string keyToTrespass;

		if (buffer[end] != ';')
		{
			//skips " ["
			beg = end + 2;

			while (buffer[end] != ']')
				++end;

			keyToTrespass = buffer.substr(beg, end - beg);
		}
		else keyToTrespass = "";

		map[zone].adjacentZones.push_back(std::make_pair(adjacent_zone, keyToTrespass));

		//needed in case there are zones that can only be entered into and not from
		map[adjacent_zone];
	}

	while (!ifs.eof())
	{
		if (ifs)
			std::getline(ifs, buffer);

		if (buffer == "")
			continue;

		size_t beg = 0, end = 0;

		while (buffer[end] != '-')
			++end;

		--end;

		std::string key = buffer.substr(beg, end - beg);

		//skips " -> "
		end += 4;

		beg = end;

		while (buffer[end] != ';')
			++end;

		std::string zone = buffer.substr(beg, end - beg);

		map[zone].keys.push_back(key);
	}

	ifs.close();

	return true;
}

//using the idea of the bfs algorithm but with a few adjustments
//
std::unordered_map<std::string, bool> GameMap::bfs(const std::string & start)
{
	std::unordered_map<std::string, bool> visited;
	for (std::pair<std::string, ZoneData> map_elem_it : map)
		visited[map_elem_it.first] = false;

	if (map.find(start) == map.end())
	{
		std::cout << "No such zone";
		return visited;
	}

	//using std::set to ensure that a key that's already available is not added
	//
	std::set<std::string> current_keys;
	if (!map[start].keys.empty())
	{
		for (std::string key : map[start].keys)
			current_keys.insert(key);
	}

	visited[start] = true;
	bfs_rec(visited, current_keys, start);

	return visited;
}


//recursively calling the function everytime a new key is found
//- "visited" contains the state of all zones at the time of function calling 
//- "keys" contains the collected keys so far
//
void GameMap::bfs_rec(std::unordered_map<std::string, bool>& visited,
	const std::set<std::string>& keys, const std::string & start)
{
	std::unordered_map<std::string, bool> visited_in_current_algorithm_run;
	for (std::pair<std::string, ZoneData> map_elem_it : map)
		visited_in_current_algorithm_run[map_elem_it.first] = false;

	std::queue<std::string> wave;

	visited_in_current_algorithm_run[start] = true;

	wave.push(start);

	while (!wave.empty())
	{
		if (map.find(wave.front()) == map.end())
		{
			wave.pop();
			continue;
		}

		if (!map[wave.front()].keys.empty())
		{
			//if it's not visited the keys of this zone might not have been used yet so we run the 
			//algorithm with this zone as a starting zone and with all the available keys including 
			//the ones from here
			//after returning from the function call with the "new" starting zone if there is a path
			//from it to a zone which is available with one of the "new" starting zone's keys that zone 
			//will be marked as visited in the "visited" container so running the algorithm with the 
			//"new" starting zone's keys and with this zone as a starting one a second time is unnecessary
			//
			if (!visited[wave.front()])
			{
				std::set<std::string> current_keys;

				for (std::string key : keys)
					current_keys.insert(key);

				size_t size = current_keys.size();
				for (std::string key : map[wave.front()].keys)
					current_keys.insert(key);

				if (current_keys.size() > size)
				{
					visited[wave.front()] = true;
					bfs_rec(visited, current_keys, wave.front());

					//the adjacent zones of this one have already been visited
					wave.pop();
					continue;
				}
			}
		}

		for (std::pair<std::string, std::string> adjacent_zone : map[wave.front()].adjacentZones)
		{
			if (!visited_in_current_algorithm_run[adjacent_zone.first])
			{
				if (adjacent_zone.second != "")
				{
					for (std::string key : keys)
					{
						if (adjacent_zone.second == key)
						{
							visited_in_current_algorithm_run[adjacent_zone.first] = true;

							//leaving the changing of the state of the zones with 
							//keys when they are currently being traversed
							if (map[adjacent_zone.first].keys.empty())
								visited[adjacent_zone.first] = true;

							wave.push(adjacent_zone.first);
							break;
						}
					}
				}
				else
				{
					visited_in_current_algorithm_run[adjacent_zone.first] = true;

					if (map[adjacent_zone.first].keys.empty())
						visited[adjacent_zone.first] = true;

					wave.push(adjacent_zone.first);
				}
			}
		}
		wave.pop();
	}
}

void GameMap::createDotFile(const std::string& path, const std::unordered_map<std::string, bool>& res)
{
	std::ofstream ofs(path);

	if (!ofs.is_open())
	{
		std::cout << "the file could not be opened!\n";
		return;
	}

	ofs << "digraph {";

	for (std::pair<std::string, bool> elem : res)
	{
		writeZoneOnDotFile(ofs, elem.first, elem.second);
	}

	ofs << '}';

	ofs.close();
}

void GameMap::writeZoneOnDotFile(std::ofstream& ofs, const std::string& zone, bool visited)
{
	if (!map[zone].keys.empty() || !visited)
	{
		ofs << "\n\"" << zone << "\"[label=\"" << zone;

		if (!map[zone].keys.empty())
		{
			for (std::string key : map[zone].keys)
			{
				ofs << "\\l" << key;
			}
		}

		if (!visited)
		{
			ofs << "\",color=red,style=filled, fillcolor=\"#ffefef";
		}

		ofs << "\"];";
	}

	for (std::pair<std::string, std::string> adj_zone : map[zone].adjacentZones)
	{
		ofs << "\n\"" << zone << "\" -> \"" << adj_zone.first;

		if (adj_zone.second != "")
			ofs << "\" [label=\"" << adj_zone.second << "\"]";
		else ofs << '\"';

		ofs << ';';
	}
	ofs << '\n';
}
