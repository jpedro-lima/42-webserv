/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:07:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/01 10:05:50 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"

Config::~Config(void) {}

Config::Config(void) {}

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
			if (server.parseServer(file, &(i)) != 0){
				this->_servers.clear();
				return ;
			}
			this->_servers.push_back(server);
		}
	}
}

// GETS
std::vector<ConfigServer>	Config::getServers(void) const {
	return(this->_servers);
}

Config	*Config::operator=(const Config *config) {
	if (this != config)
		this->_servers = (*config)._servers;
	return (this);
}
