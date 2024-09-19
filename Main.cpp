
#include "FileReader.hpp"
#include "Webserv.hpp"

int main() {

	FileReader *file = new FileReader("./test.conf");

	std::cout << file->getFullFile() << std::endl;
	return 0;
}