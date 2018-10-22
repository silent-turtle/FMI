#include "PostLink.h"


PostLink::PostLink(const char* str, const char* link_str, size_t num) : Post(str, num), link(nullptr)
{
	setLink(link_str);
}

PostLink::~PostLink()
{
	delete[] link;
}

void PostLink::createHTMLFile(std::ofstream& ofs) const
{
	if (ofs) ofs << "<a href=\"" << getLink() << "\">" << getDescription() << "</a>";
}

void PostLink::setLink(const char* str)
{
	size_t size = strlen(str);
	char* newMem;
	try
	{
		newMem = new char[size + 1];
	}
	catch (std::bad_alloc&)
	{
		throw;
	}

	strncpy(newMem, str, size);
	newMem[size] = '\0';

	if (description) delete[] link;

	link = newMem;
}