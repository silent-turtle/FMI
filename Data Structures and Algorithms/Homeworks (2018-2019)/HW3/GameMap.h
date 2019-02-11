#ifndef GAME_MAP_HDR
#define GAME_MAP_HDR

#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<set>
#include<queue>
#include<unordered_map>

class GameMap
{
public:
	GameMap() = default;
	GameMap(const GameMap&) = default;
	GameMap& operator=(const GameMap&) = default;
	~GameMap() = default;

public:
	bool loadDataFromFile(const std::string& path);
	std::unordered_map<std::string, bool> bfs(const std::string& start);
	void createDotFile(const std::string& path, const std::unordered_map<std::string, bool>& res);

private:
	struct ZoneData
	{
		//pair consists of zone name and a key needed in order to visit the zone
		//"" if there's no key
		std::list<std::pair<std::string, std::string>> adjacentZones;
		std::list<std::string> keys;
	};

private:
	std::unordered_map<std::string, ZoneData> map;
	
private:
	void bfs_rec(std::unordered_map<std::string, bool>& visited, 
		const std::set<std::string>& keys, const std::string& start);
	void writeZoneOnDotFile(std::ofstream& ofs, const std::string& zone, bool visited);
};

#endif // !GAME_MAP_HDR
