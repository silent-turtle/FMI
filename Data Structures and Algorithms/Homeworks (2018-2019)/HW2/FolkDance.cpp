#include "FolkDance.h"

const size_t MAX_NAME_SIZE = 30;
const size_t MAX_CHAIN_SIZE = 5;

FolkDance::FolkDance() : table(2)
{
}

void FolkDance::menu(const std::string& path)
{
	loadFromFile(path);

	help();

	std::string buffer;
	std::string command;
	do
	{
		try
		{
			std::cout << "\n>";
			std::getline(std::cin, buffer);
			size_t begin = 0, end = 0;

			command = createString(buffer, begin, end, ' ');

			if (buffer[end] != '\0')
			{
				while (buffer[end] == ' ')
					++end;
				begin = end + 1;
			}

			if (command == "add")
			{
				std::string name = createString(buffer, begin, end, '\"');
				//++end;
				while (buffer[end] == ' ')
					++end;
				begin = end + 1;

				std::string name_left = createString(buffer, begin, end, '\"');
				//++end;
				while (buffer[end] == ' ')
					++end;
				begin = end + 1;

				std::string name_right = createString(buffer, begin, end, '\"');

				add(name, name_left, name_right);

				continue;
			}

			if (command == "remove")
			{
				std::string name = createString(buffer, begin, end, '\"');

				remove(name);
				continue;
			}

			if (command == "swap")
			{
				std::string name1 = createString(buffer, begin, end, '\"');
				while (buffer[end] == ' ')
					++end;
				begin = end + 1;

				std::string name2 = createString(buffer, begin, end, '\"');

				swap(name1, name2);
				continue;
			}

			if (command == "release")
			{
				std::string name = createString(buffer, begin, end, '\"');
				while (buffer[end] == ' ')
					++end;
				begin = end;

				std::string side = createString(buffer, begin, end, ' ');

				release(name, side);
				continue;
			}

			if (command == "grab")
			{
				std::string name = createString(buffer, begin, end, '\"');
				while (buffer[end] == ' ')
					++end;
				begin = end;

				std::string side = createString(buffer, begin, end, ' ');

				grab(name, side);
				continue;
			}

			if (command == "print")
			{
				print();
				continue;
			}

			if (command == "info")
			{
				std::string name = createString(buffer, begin, end, '\"');

				info(name);
				continue;
			}

			if (command == "help")
			{
				help();
				continue;
			}

			if (command != "exit")
			{
				std::cout << "Unknown command!\n\n";

				std::cin.clear();
			}

		}
		catch (std::exception& e)
		{
			std::cout << e.what();

			if (!strcmp(e.what(), "...and the music stops!"))
				break;
		}
	} while (command != "exit");
}

void FolkDance::loadFromFile(const std::string & path)
{
	std::ifstream ifs(path);
	if (!ifs.is_open())
	{
		std::cout << "The file could not be opened!\n";
		return;
	}

	char previous_name[MAX_NAME_SIZE], current_name[MAX_NAME_SIZE], first_name[MAX_NAME_SIZE];
	ifs.getline(previous_name, MAX_NAME_SIZE + 1);

	strncpy_s(first_name, MAX_NAME_SIZE, previous_name, MAX_NAME_SIZE);
	strncpy_s(current_name, MAX_NAME_SIZE, previous_name, MAX_NAME_SIZE);

	insert(previous_name);
	lead_name = previous_name;

	//in case a name appears more than once while reading from the file,
	//adds the name the first time and ignores every other appearance
	bool nameIsTaken = false;

	while (!ifs.eof())
	{
		if (!nameIsTaken)
			strncpy_s(previous_name, MAX_NAME_SIZE, current_name, MAX_NAME_SIZE);

		nameIsTaken = false;
		ifs.getline(current_name, MAX_NAME_SIZE + 1);

		//the insert method checks if the name is used but I do it manually
		//here so that the rest of the names can be loaded from the file
		if (!nameExists(current_name))
		{
			insert(current_name, previous_name);
			size_t index_previous = hash_func(previous_name);
			std::list<Person>::iterator previous = findPerson(previous_name, index_previous);
			previous->left = current_name;
		}
		else nameIsTaken = true;
	}

	ifs.close();

	//if the last name from the file is a name that's already added
	//use the last added name instead
	if (nameIsTaken)
		strncpy_s(current_name, MAX_NAME_SIZE, previous_name, MAX_NAME_SIZE);

	//adds the last person as a right neighbour of the first
	//and the first person as a left neighbour of the last
	size_t index_first = hash_func(first_name), index_last = hash_func(current_name);
	std::list<Person>::iterator first = findPerson(first_name, index_first);
	std::list<Person>::iterator last = findPerson(current_name, index_last);

	last->left = first->name;
	first->right = current_name;
}

void FolkDance::print()
{
	size_t index = hash_func(lead_name);
	std::list<Person>::iterator current = findPerson(lead_name, index);

	do
	{
		std::cout << current->name << '\n';
		size_t neighbour_index = hash_func(current->left);
		current = findPerson(current->left, neighbour_index);
	} while (current->name != lead_name);
}

void FolkDance::info(const std::string & name)
{
	size_t index = hash_func(name);

	if (!nameExists(name))
	{
		throw std::logic_error("The person doesn't exist!\n");
	}

	std::list<Person>::iterator current = findPerson(name, index);
	std::cout << current->left;

	if (current->hasGrabbedLeft)
		std::cout << " <";
	else std::cout << " -";

	std::cout << "--";

	size_t index_left = hash_func(current->left);
	std::list<Person>::iterator left = findPerson(current->left, index_left);

	if (left->hasGrabbedRight)
		std::cout << "> ";
	else std::cout << "- ";

	std::cout << current->name;

	size_t index_right = hash_func(current->right);
	std::list<Person>::iterator right = findPerson(current->right, index_right);

	if (right->hasGrabbedLeft)
		std::cout << " <";
	else std::cout << " -";

	std::cout << "--";

	if (current->hasGrabbedRight)
		std::cout << "> ";
	else std::cout << "- ";

	std::cout << current->right << "\n\n";
}

void FolkDance::release(const std::string & name, const std::string & choice)
{
	size_t index = hash_func(name);

	if (!nameExists(name))
		throw std::logic_error("The person doesn't exist!\n");

	std::list<Person>::iterator current = findPerson(name, index);

	if (choice == "left")
	{
		current->hasGrabbedLeft = false;
		return;
	}

	if (choice == "right")
	{
		current->hasGrabbedRight = false;
		return;
	}

	if (choice == "both")
	{
		current->hasGrabbedLeft = false;
		current->hasGrabbedRight = false;
		return;
	}

	throw std::logic_error("Unknown command - should be left/right/both\n");
}

void FolkDance::grab(const std::string & name, const std::string & choice)
{
	size_t index = hash_func(name);

	if (!nameExists(name))
		throw std::logic_error("The person doesn't exist!\n");

	std::list<Person>::iterator current = findPerson(name, index);

	if (choice == "left")
	{
		current->hasGrabbedLeft = true;
		return;
	}

	if (choice == "right")
	{
		current->hasGrabbedRight = true;
		return;
	}

	if (choice == "both")
	{
		current->hasGrabbedLeft = true;
		current->hasGrabbedRight = true;
		return;
	}

	throw std::logic_error("Unknown command - should be left/right/both\n");
}

void FolkDance::add(const std::string & name, const std::string & label_left, const std::string & label_right)
{
	size_t index_left = hash_func(label_left), index_right = hash_func(label_right);

	if (!nameExists(label_left) || !nameExists(label_right))
		throw std::logic_error("One (or both) of the neighbours doesn't exist!\n");

	std::list<Person>::iterator left = findPerson(label_left, index_left);
	std::list<Person>::iterator right = findPerson(label_right, index_right);

	if (!areNeighbours(left, right))
	{
		throw std::logic_error("The people aren't neighbours!\n");
	}

	insert(name, label_right, label_left);

	left->right = name;
	right->left = name;

	left->hasGrabbedRight = true;
	right->hasGrabbedLeft = true;
}

void FolkDance::remove(const std::string & name)
{
	size_t index = hash_func(name);

	if (!nameExists(name))
		throw std::logic_error("The person doesn't exist!\n");

	std::list<Person>::iterator current = findPerson(name, index);
	
	size_t index_left = hash_func(current->left), index_right = hash_func(current->right);
	std::list<Person>::iterator left = findPerson(current->left, index_left);
	std::list<Person>::iterator right = findPerson(current->right, index_right);

	if (!current->hasGrabbedLeft && !current->hasGrabbedRight && !left->hasGrabbedRight && !right->hasGrabbedLeft)
	{
		//if left and right are neighbours then there are only
		//three people including the one to be removed
		if (areNeighbours(left, right) || areNeighbours(right, left))
			throw std::exception("...and the music stops!");

		left->right = right->name;
		right->left = left->name;

		//if the first person is deleted, change to the first on the left
		if (name == lead_name)
			lead_name = current->left;

		table[index].erase(current);
		std::cout << "Free at last!\n";

	}
	else std::cout << "This won't be easy!\n";
}

void FolkDance::swap(const std::string & name1, const std::string & name2)
{
	size_t index1 = hash_func(name1), index2 = hash_func(name2);

	if (!nameExists(name1) || !nameExists(name2))
		throw std::logic_error("One (or both) of the people doesn't exist!\n");

	std::list<Person>::iterator first = findPerson(name1, index1), second = findPerson(name2, index2);
	std::list<Person>::iterator left, right;

	if (areNeighbours(first, second))
	{
		size_t index_left = hash_func(first->left), index_right = hash_func(second->right);
		left = findPerson(first->left, index_left);
		right = findPerson(second->right, index_right);

		if (!first->hasGrabbedLeft && !second->hasGrabbedRight && !left->hasGrabbedRight && !right->hasGrabbedLeft)
		{
			//person(left_neighbour|right_neighbour)
			//before swap: left(...|first) - first(left|second) - second(first|right) - right(second|...)
			//
			//left(...|first) - second(first|right) - first(left|second) - right(second|...)
			//left(...|second) - second(first|right) - first(left|second) - right(first|...)
			//left(...|second) - second(first|left) - first(right|second) - right(first|...)
			//left(...|second) - second(left|first) - first(right|second) - right(first|...)
			//left(...|second) - second(left|first) - first(second|right) - right(first|...)

			std::swap(first, second);
			std::swap(left->right, right->left);
			std::swap(first->right, second->left);
			std::swap(first->left, first->right);
			std::swap(second->left, second->right);
			std::swap(first->hasGrabbedLeft, first->hasGrabbedRight);
			std::swap(second->hasGrabbedLeft, second->hasGrabbedRight);
		}
	}
	else
		if (areNeighbours(second, first))
		{
			size_t index_left = hash_func(second->left), index_right = hash_func(first->right);
			left = findPerson(second->left, index_left);
			right = findPerson(first->right, index_right);

			if (!second->hasGrabbedLeft && !first->hasGrabbedRight && !left->hasGrabbedRight && !right->hasGrabbedLeft)
			{
				std::swap(first, second);
				std::swap(left->right, right->left);
				std::swap(second->right, first->left);
				std::swap(first->left, first->right);
				std::swap(second->left, second->right);
				std::swap(first->hasGrabbedLeft, first->hasGrabbedRight);
				std::swap(second->hasGrabbedLeft, second->hasGrabbedRight);
			}
		}
}

//taken from Ivan Filipov's hash table implementation
size_t FolkDance::hash_func(const std::string& str)
{
	size_t result = str.size();
	for (unsigned char c : str)
	//for(size_t i = 0; i < str.size(); ++i)
		result += c;

	return result & (table.size() - 1);
}

void FolkDance::rehash()
{
	FolkDance temp_table;
	temp_table.table.resize(table.size() * 2);

	for (size_t i = 0; i < table.size(); ++i)
	{
		if (!table[i].empty())
		{
			for (std::list<Person>::iterator it = table[i].begin(); it != table[i].end(); ++it)
			{
				temp_table.insert(it->name, it->left, it->right);
			}
		}
	}

	table = temp_table.table;
}

void FolkDance::insert(const std::string & name, const std::string& left, const std::string& right)
{
	size_t index = hash_func(name);

	if (nameExists(name))
	{
		throw std::logic_error("The name is already used!\n");
	}

	if (table[index].size() >= MAX_CHAIN_SIZE)
	{
		rehash();
		index = hash_func(name);
	}

	Person temp(name, left, right);
	table[index].push_back(temp);
}

std::list<FolkDance::Person>::iterator FolkDance::findPerson(const std::string & name, size_t index)
{
	std::list<FolkDance::Person>::iterator it = table[index].begin();

	for (; it != table[index].end() && it->name != name; ++it);

	return it;
}

bool FolkDance::areNeighbours(const std::list<Person>::iterator & it1, const std::list<Person>::iterator & it2)
{
	return (it1->name == it2->left);
}

bool FolkDance::nameExists(const std::string & name)
{
	size_t index = hash_func(name);

	for (std::list<Person>::iterator it = table[index].begin(); it != table[index].end(); ++it)
		if (name == it->name)
			return true;

	return false;
}

void FolkDance::help()
{
	std::cout << "What would you like to do?\n"
		<< "1> add <\"name\"> <\"left\"> <\"right\">;\n"
		<< "2> remove <\"name\">;\n"
		<< "3> swap <\"name1\"> <\"name2\">;\n"
		<< "4> release <\"name\"> <side>;\n"
		<< "5> grab <\"name\"> <side>;;\n"
		<< "6> print;\n"
		<< "8> info <\"name\">;\n"
		<< "9> help;\n"
		<< "10> exit.\n";
}

size_t FolkDance::getIndex(std::string str, size_t begin, char c)
{
	size_t res = begin;

	while (str[res] != c && str[res] != '\0')
	{
		++res;
	}

	return res;
}

std::string FolkDance::createString(std::string str, size_t& begin, size_t& end, char c)
{
	std::string temp;

	end = getIndex(str, begin, c);

	temp = str.substr(begin, end - begin);

	if (str[end] != '\0')
		++end;

	return temp;
}
