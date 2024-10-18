/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:07:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/17 12:19:41 by joapedr2         ###   ########.fr       */
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
		Config::checkServers();
	}
	catch (const std::exception &e) {
		if (this->_servers.size() > 0)
			this->_servers.clear();
		throw;
	}
}

void	Config::parser(fileVector file) {
	try {
		for (size_t i = 0; i < file.size(); i++) {
			if (file[i] == "server") {
				ConfigServer  server;
				server.parseServer(file, &(i));
				this->_servers.push_back(server);
			}
		}
	}
	catch (const std::exception &){throw;}
}

void	Config::checkServers() {
	std::vector<t_listen> listens = this->getAllListens();
	std::vector<t_listen>::iterator	i;
	std::vector<t_listen>::iterator	j;

	for (i = listens.begin(); i != listens.end(); i++) {
		for (j = listens.begin(); j != listens.end(); j++) {
			if (j == i) {continue;}
			if (i->host == j->host && i->port == j->port)	
				throw Exceptions::ExceptionInvalidListenServers();
		}
	}
}

// GETTTERS
std::vector<ConfigServer>	Config::getServers(void) const {return(this->_servers);}

std::vector<t_listen>		Config::getAllListens(void) const {
	std::vector<t_listen>	ret;
	for (std::vector<ConfigServer>::const_iterator server = this->_servers.begin(); server != this->_servers.end(); server++) {
		std::vector<t_listen>	serverListen = server->getListen();
		for (std::vector<t_listen>::iterator listen = serverListen.begin(); listen != serverListen.end(); listen++) {
			ret.push_back(*listen);
		}
	}
	return (ret);
};

Config	*Config::operator=(const Config *config) {
	if (this != config)
		this->_servers = (*config)._servers;
	return (this);
}

RequestConfig	Config::getConfigForRequest(t_listen const address, Request &request) const {
	std::string	uri = request.getPath();
	std::string	locationPath;
	
	ConfigServer server = this->getServerForRequest(address, request.getHeaders().at("Host"));
	server = server.getLocationForRequest(uri, locationPath);
	if (*(--locationPath.end()) == '/')
		locationPath.resize(locationPath.size() - 1);
	RequestConfig config(server, request, uri, request.getMethod(), locationPath);
	
	config.setHostPort(address);
	return (config);
}

ConfigServer	Config::getServerForRequest(t_listen const address, std::string const hostName) const {
	std::vector<ConfigServer>	possibleServers;

	std::vector<ConfigServer>::const_iterator server;
	for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
		std::vector<t_listen>	listens = server->getListen();
		for (std::vector<t_listen>::iterator listenIter = listens.begin(); listenIter != listens.end(); listenIter++) {
			if (address.host == (*listenIter).host && address.port == (*listenIter).port)
				possibleServers.push_back((*server));
		}
	}
	if (possibleServers.empty())
		throw Exceptions::ExceptionServerListen();
	for (std::vector<ConfigServer>::iterator serversIter = possibleServers.begin() ; serversIter != possibleServers.end(); serversIter++) {
		std::vector<std::string>	serverNames = serversIter->getServerName();
		for (std::vector<std::string>::iterator servNameIter = serverNames.begin() ; servNameIter != serverNames.end(); servNameIter++) {
			if (*servNameIter == hostName) {
				return (*serversIter);
			}
		}
	}
	return (possibleServers[0]);
}
