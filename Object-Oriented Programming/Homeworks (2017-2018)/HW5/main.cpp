#include"MessageCollection.h"

const size_t MAX_BUFFER_SIZE = 32;

int main()
{
	MessageCollection mc;

	mc.setMessages("file.txt");
	/*mc.setSize("file.txt");

	mc.deserialise("file.txt");*/

	std::cout << "-- Hashtags:" <<std::endl;
	mc.printHashtags();

	const char* msg = "fmiLife";

	mc += msg;

	std::cout << "-- The message closest to \"" << msg << "\" is:" 
		<< std::endl << mc[msg] << std::endl;

	std::cout << "-- Messages arranged by proximity to \"" << msg << "\":" << std::endl;
	mc.printCompare(msg);

	return 0;
} 