
#include "FileReader.hpp"
#include "Webserv.hpp"

int main() {
	std::string str;
	FileReader *file = new FileReader("./test.conf");

	str = file->getFullFile();

	// size_t	pos = 0;
	// size_t	openKeys = 0;
	// while ((pos = str.find("{", pos)) != std::string::npos && pos++)
	// 	openKeys++;
	// pos = 0;
	// size_t	closeKeys = 0;
	// while ((pos = str.find("}", pos)) != std::string::npos && pos++)
	// 	closeKeys++;

	size_t	openKeys = 0, closeKeys = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '{')
			openKeys++;
		if (str[i] == '}')
			closeKeys++;
	}

	std::cout << openKeys << std::endl;
	std::cout << closeKeys << std::endl;
	return 0;
}