/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/20 23:16:05 by joapedr2         ###   ########.fr       */
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

	inFile.close();
	return (textBuffer);
}

const std::string	FileReader::getFullFile(void) const {
	return (this->_fullFile);
}

bool	FileReader::checkerConfigfFile(const std::string file) {
	size_t	openKeys = 0, closeKeys = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '{')
			openKeys++;
		if (str[i] == '}')
			closeKeys++;
	}
	if (openKeys != closeKeys)
		throw FileReader::ConfigFileErrorException();
	if (file.find("root") == td::string::npos)
		throw FileReader::ConfigFileErrorException();
	if (file.find("index") == td::string::npos)
		throw FileReader::ConfigFileErrorException();
}

const char	*FileReader::ConfigFileErrorException::what() const throw() {
	return "Exception thrown: Configuration file error";
}

const char	*FileReader::FileNotFoundException::what() const throw() {
	return "Exception thrown: could not open configuration file";
}
