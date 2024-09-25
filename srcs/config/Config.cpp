/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:07:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/25 17:47:06 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::~Config(void) {};

Config::Config(const char *configPath) {
	try {
		this->_configText = FileReader::readFile(configPath);
		this->_fileVector = FileReader::split(this->_configText, " \f\n\r\t\v\0");
		Config::parser(this->_fileVector);
	}
	catch (const std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
}

void	Config::parser(fileVector file) {
	for (size_t i = 0; i < file.size(); i++) {
		if (file[i] == "server") {
			ConfigServer  server;
			if (file[++i] != "{")
				throw Exceptions::ExpectedCurlyBracketsBefore();
			try {
				server.parseServer(file, &(++i));
			}
			catch (const std::exception &e) {
				std::cerr << RED << e.what() << RESET << std::endl;
				return ;
			}
			this->_servers.push_back(server);
		}
	}
}