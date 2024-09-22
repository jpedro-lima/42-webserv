/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 05:15:00 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileReader.hpp"

FileReader::~FileReader(void) {}

FileReader::FileReader(const char *filename) : _fullFile(readFile(filename)) {}

std::string	FileReader::readFile(const char *filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open())
		throw FileReader::FileNotFoundException();
	if(inFile.peek() == std::ifstream::traits_type::eof())
		throw FileReader::ConfigFileErrorException();
	std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string textBuffer = strStream.str();
	textBuffer += " ";
	inFile.close();

	return (textBuffer);
}

std::string	FileReader::getFullFileText(void) const {
	return (this->_fullFile);
}

void	FileReader::checkerConfigFile(void) const {
	size_t	openKeys = 0, closeKeys = 0;
	for (size_t i = 0; i < this->_fullFile.length(); i++)
	{
		if (this->_fullFile[i] == '{')
			openKeys++;
		if (this->_fullFile[i] == '}')
			closeKeys++;
	}
	if (openKeys != closeKeys)
		throw FileReader::ConfigFileErrorException();
	if (Utils::findMembers("server", this->_fullFile) == std::string::npos)
		throw FileReader::ConfigFileErrorException();
	if (Utils::findMembers("root", this->_fullFile) == std::string::npos)
		throw FileReader::ConfigFileErrorException();
	if  (Utils::findMembers("index", this->_fullFile) == std::string::npos)
		throw FileReader::ConfigFileErrorException();
}


// fileVector	FileReader::split(const std::string charset) {
// 	fileVector	vectorReturn;

// 	std::string::size_type	start = this->_fullFile.find_first_not_of(charset, 0);
// 	std::string::size_type	end = 0;
// 	do
// 	{
// 		end = this->_fullFile.find_first_of(charset, start);
// 		if (end == std::string::npos) {
// 			break;
// 		}
// 		std::string	str = this->_fullFile.substr(start, end - start);
// 		vectorReturn.push_back(str);
// 	} while ((start = this->_fullFile.find_first_not_of(charset, end)) != std::string::npos);
	
// 	return (vectorReturn);
// }

const char	*FileReader::ConfigFileErrorException::what() const throw() {
	return "Exception thrown: Configuration file error";
}

const char	*FileReader::FileNotFoundException::what() const throw() {
	return "Exception thrown: could not open configuration file";
}
