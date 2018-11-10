#include "CongaLine.h"



CongaLine::CongaLine() : head(nullptr), tail(nullptr)
{
}

CongaLine::CongaLine(const CongaLine& other)
{
	Person* temp = other.head;
	if (temp)
	{
		head = new Person(temp->name, temp->uni);
		temp = temp->next;

		if (temp)
		{
			tail = new Person(temp->name, temp->uni);
			head->next = tail;
			tail->prev = head;

			temp = temp->next;
		}

		while (temp)
		{
			Person* temp2 = new Person(temp->name, temp->uni);

			tail->next = temp2;
			temp2->prev = tail;
			tail = temp2;

			temp = temp->next;
		}
	}
}

CongaLine & CongaLine::operator=(const CongaLine& other)
{
	if (this != &other)
	{
		clean();

		Person* temp = other.head;
		if (temp)
		{
			head = new Person(temp->name, temp->uni);
			temp = temp->next;

			if (temp)
			{
				tail = new Person(temp->name, temp->uni);
				head->next = tail;
				tail->prev = head;

				temp = temp->next;
			}

			while (temp)
			{
				Person* temp2 = new Person(temp->name, temp->uni);

				tail->next = temp2;
				temp2->prev = tail;
				tail = tail->next;

				temp = temp->next;
			}
		}
	}

	return *this;
}


CongaLine::~CongaLine()
{
	clean();
}

void CongaLine::append(const char* name, const char* uni)
{
	if (head == nullptr)
	{
		head = new Person(name, uni);

		return;
	}

	if (tail == nullptr)
	{
		if (compareUni(head->uni, uni))
		{
			tail = new Person(name, uni);
			head->next = tail;
			tail->prev = head;

			return;
		}

		throw std::invalid_argument("Incompatible people\n");
	}

	if (compareUni(tail->uni, uni))
	{
		Person* temp = new Person(name, uni);
		tail->next = temp;
		temp->prev = tail;

		tail = tail->next;

		return;
	}

	throw std::invalid_argument("Incompatible people\n");
}

void CongaLine::append(const Iterator& it)
{
	if (head == nullptr)
		head = it.getPtr();
	else
	{
		if (tail == nullptr)
		{
			if (compareUni(head->uni, it.getUni()))
			{
				Person* temp = it.getPtr();
				head->next = temp;
				temp->prev = head;
			}
			else
				throw std::invalid_argument("Incompatible people\n");
		}
		else
		{
			if (compareUni(tail->uni, it.getUni()))
			{
				Person* temp = it.getPtr();
				tail->next = temp;
				temp->prev = tail;
			}
			else
				throw std::invalid_argument("Incompatible people\n");
		}
	}

	Person* temp = head->next;

	while (temp)
	{
		tail = temp;
		temp = temp->next;
	}
}

void CongaLine::removeAtFirst()
{
	if (head)
	{
		Person* temp = head->next;
		delete head;
		head = temp;
	}
}

void CongaLine::removeAtLast()
{
	if (tail)
	{
		Person* temp = tail;
		tail = tail->prev;
		delete temp;
		tail->next = nullptr;
	}
	else
		removeAtFirst();
}

void CongaLine::remove(const Iterator& it)
{
	Person* prev = it.getPtr()->prev;
	it.getPtr()->next->prev = nullptr;

	delete prev->next;
	prev->next = nullptr;

	if (head != prev)
		tail = prev;
	else
		tail = nullptr;
}

CongaLine::Iterator CongaLine::find(const char* name) const
{
	Person* temp = head;

	while (temp)
	{
		if (!strcmp(temp->name, name))
			return Iterator(temp);
		temp = temp->next;
	}
	return Iterator(nullptr);
}

void CongaLine::print() const
{
	Person* temp = head;

	while (temp)
	{
		std::cout << '(' << temp->name << ", " << temp->uni << ')';
		if (temp->next) std::cout << " - ";

		temp = temp->next;
	}
}

void CongaLine::clean()
{
	while (head)
		removeAtFirst();
}

bool CongaLine::compareUni(const char* uni1, const char* uni2)
{
	if (!strcmp(uni1, "unss") && !strcmp(uni2, "fmi") || !strcmp(uni1, "fmi") && !strcmp(uni2, "tu")
		|| !strcmp(uni1, "tu") && !strcmp(uni2, "unss"))
		return false;

	return true;
}

CongaLine::Person::Person(const char* name, const char* uni)
{
	setName(name);

	try
	{
		setUni(uni);
	}
	catch (std::bad_alloc&)
	{
		delete[] name;

		throw;
	}
}

CongaLine::Person::~Person()
{
	if (name) 
		delete[] name;

	if (uni) 
		delete[] uni;
}

void CongaLine::Person::setName(const char* name)
{
	size_t size = strlen(name);

	this->name = new char[size + 1];

	strncpy_s(this->name, size + 1, name, size);
}

void CongaLine::Person::setUni(const char * uni)
{
	size_t size = strlen(uni);

	this->uni = new char[size + 1];

	strncpy_s(this->uni, size + 1, uni, size);
}