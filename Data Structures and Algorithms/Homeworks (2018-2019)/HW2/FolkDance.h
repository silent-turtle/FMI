#ifndef FOLK_DANCE_HDR
#define FOLK_DANCE_HDR

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

class FolkDance
{
public:
	FolkDance();
	FolkDance(const FolkDance&) = default;
	FolkDance& operator=(const FolkDance&) = default;
	~FolkDance() = default;

	void menu(const std::string& path);

private:
	struct Person
	{
		std::string name, left, right;
		bool hasGrabbedLeft = true, hasGrabbedRight = true;

		Person(const std::string& n, const std::string& r = "", const std::string& l = "") : name(n), right(r), left(l) { ; }
	};

private:
	std::vector<std::list<Person>> table;
	std::string lead_name;

private:
	void print();
	void info(const std::string& name);

	void release(const std::string& name, const std::string& choice);
	void grab(const std::string& name, const std::string& choice);

	void add(const std::string& name, const std::string& label_left, const std::string& label_right);
	void remove(const std::string& name);
	void swap(const std::string& name1, const std::string& name2);

private:
	size_t hash_func(const std::string& str);
	void rehash();
	void insert(const std::string& name, const std::string& left = "", const std::string& right = "");
	std::list<Person>::iterator findPerson(const std::string& name, size_t index);

	void loadFromFile(const std::string& path);
	void help();
	size_t getIndex(std::string str, size_t begin, char c);
	std::string createString(std::string str, size_t& begin, size_t& end, char c);
	bool areNeighbours(const std::list<Person>::iterator& it1, const std::list<Person>::iterator& it2);
	bool nameExists(const std::string& name);
};

#endif // !FOLK_DANCE_HDR
