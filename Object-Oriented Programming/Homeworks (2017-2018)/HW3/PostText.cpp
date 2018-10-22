#include "PostText.h"




PostText::PostText(const char* str, size_t num) : Post(str, num)
{
}

void PostText::createHTMLFile(std::ofstream& ofs) const
{
	if (ofs) ofs << "<body>" << getDescription() << "</body>";
}
