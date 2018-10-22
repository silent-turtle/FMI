#include "PostPicture.h"



PostPicture::PostPicture(const char* str, size_t num) : Post(str, num)
{
}

void PostPicture::createHTMLFile(std::ofstream& ofs) const
{
	if(ofs) ofs << "<img src=\"" << getDescription() << "\">";
}

