/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:07:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 19:52:17 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::~Config(void) {};

Config::Config(std::string configPath) {
	try {
		this->_configText = FileReader::readFile(configPath);
		this->_fileVector = FileReader::split(this->_configText);
		Config::parser(this->fileVector);
	}
	catch (const std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
}
̣
void	Config::parser(fileVector file) {
	for (size_t i = 0; i < file.size(); i++) {
		if (file[i] == "server") {
			ConfigServer  server;
			if (file[++i] != "{")
				throw ExpectedCurlyBracketsAfter();
			try {
				server.parseServer(++i, file)
			}
			catch (const std::exception &e) {
				std::cerr << RED << e.what() << RESET << std::endl;
			}
			this->_servers.push_back(server);
		}
	}
}