/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/19 00:25:30 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileReader.hpp"

FileReader::~FileReader(void) {}

FileReader::FileReader(const char *filename) : _fullFile(readFile(filename)) {}

std::string	FileReader::readFile(const char *filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open())
		throw FileReader::FileNotFoundException();

	std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string textBuffer = strStream.str();

	inFile.close();

	return (textBuffer);
}

const std::string	FileReader::getFullFile(void) const {
	return (this->_fullFile);
}

const char	*FileReader::FileNotFoundException::what() const throw() {
	return "Exception thrown: could not open configuration file";
}
