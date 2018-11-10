#ifndef CONGA_HDR
#define CONGA_HDR

#include"CongaLine.h"

class Conga
{
public:
	Conga();
	~Conga();

public:
	void menu();
	
private:
	CongaLine** cl;
	size_t size;
	size_t capacity;

private:
	void append(const char* name, const char* uni, size_t index);
	void removeAtFirst(size_t index);
	void removeAtLast(size_t index);
	void remove(const char* name, size_t index);
	void merge(size_t index1, size_t index2);
	void print() const;
	void help() const;
	
private:
	void resize(size_t);
	void clean();
	void swap(CongaLine*, CongaLine*);
};

#endif // !CONGA_HDR
