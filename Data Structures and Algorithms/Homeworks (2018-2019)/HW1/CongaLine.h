#ifndef CONGA_LINE_HDR
#define CONGA_LINE_HDR

#include <iostream>


class CongaLine
{
public:
	CongaLine();
	CongaLine(const CongaLine&);
	CongaLine& operator=(const CongaLine&);
	~CongaLine();

public:
	class Iterator;

public:
	void append(const char* name, const char* uni);
	void append(const Iterator&);
	void removeAtFirst();
	void removeAtLast();
	void remove(const Iterator&);
	void print() const;

	Iterator find(const char* name) const;
	const char* getTailName() const { if (tail) return tail->name; else return nullptr; }

private:
	struct Person
	{
		char* name = nullptr;
		char* uni = nullptr;
		Person* next = nullptr;
		Person* prev = nullptr;

		Person(const char* name, const char* uni);
		~Person();

		void setName(const char* name);
		void setUni(const char* uni);
	};

	Person* head;
	Person* tail;

	void clean();
	bool compareUni(const char*, const char*);

public:

	class Iterator
	{
	public:
		Iterator() : dataptr(nullptr) { ; }
		Iterator(Person* p) : dataptr(p) { ; }
		~Iterator() { ; }

	public:
		const char* getName() const { return dataptr->name; }
		const char* getUni() const { return dataptr->uni; }
		Person* getPtr() const { return dataptr; }

		bool operator==(const Iterator& other) { return dataptr == other.dataptr; }
		bool operator!=(const Iterator& other) { return !(*this == other); }
		Iterator& operator++() { dataptr = dataptr->next; return *this; }
		Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

	private:
		Person* dataptr;
	};

	Iterator begin() const { return Iterator(head); }
	Iterator end() const { return Iterator(nullptr); }
};

#endif // !CONGA_LINE_HDR
