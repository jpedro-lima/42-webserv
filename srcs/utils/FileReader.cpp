/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/25 16:35:51 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileReader.hpp"

namespace FileReader {
	
	std::string	readFile(const char *filename) {
		std::ifstream inFile(filename);
		if (!inFile.is_open())
			throw Exceptions::FileNotFoundException();
		if(inFile.peek() == std::ifstream::traits_type::eof())
			throw Exceptions::ConfigFileEmptyException();
		
		std::stringstream strStream;
		strStream << inFile.rdbuf();
		std::string textBuffer = strStream.str();
		textBuffer += " ";
		inFile.close();

		return (textBuffer);
	}

	void	checkerConfigFile(const std::string fileText) {
		size_t	openKeys = 0, closeKeys = 0;
		for (size_t i = 0; i < fileText.length(); i++)
		{
			if (fileText[i] == '{')
				openKeys++;
			if (fileText[i] == '}')
				closeKeys++;
		}
		if (openKeys != closeKeys)
			throw Exceptions::ConfigFileErrorException();
		if (Utils::findMembers("server", fileText) == std::string::npos)
			throw Exceptions::ConfigFileErrorException();
		if (Utils::findMembers("root", fileText) == std::string::npos)
			throw Exceptions::ConfigFileErrorException();
		if (Utils::findMembers("index", fileText) == std::string::npos)
			throw Exceptions::ConfigFileErrorException();
	}

	fileVector	split(std::string fileText, const std::string charset) {
		fileVector	vectorReturn;

		std::string::size_type	start = fileText.find_first_not_of(charset, 0);
		std::string::size_type	end = 0;
		do
		{
			end = fileText.find_first_of(charset, start);
			if (end == std::string::npos) {
				break;
			}
			std::string	str = fileText.substr(start, end - start);
			vectorReturn.push_back(str);
		} while ((start = fileText.find_first_not_of(charset, end)) != std::string::npos);
		
		return (vectorReturn);
	}

}
