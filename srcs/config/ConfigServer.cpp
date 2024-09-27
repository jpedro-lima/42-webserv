/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/27 17:06:45 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::~ConfigServer() {};

ConfigServer::ConfigServer(void){
	this->_listen.clear();
	this->_root.clear();
	this->_index.clear();
	this->_server_name.push_back("Default");
	this->_error_pages = ConfigDefault::defaultErrorPages();
	this->_client_body_buffer_size = 10000000;
	this->_allowed_methods = ConfigDefault::defaultAllowMethods();
	this->_autoindex = false;
	this->_location.clear();
	this->_serverParsingMap = this->_initParseMap();
	this->_locationParsingMap = this->_initParseMap();
}

parseMap ConfigServer::_initParseMap() {
	parseMap	myMap;
	myMap["listen"] = &ConfigAdd::addListen;
	myMap["root"] = &ConfigAdd::addRoot;
	myMap["server_name"] = &ConfigAdd::addServerName;
	myMap["error_page"] = &ConfigAdd::addErrorPages;
	myMap["client_body_buffer_size"] = &ConfigAdd::addClientBodyBufferSize;
	myMap["allow_methods"] = &ConfigAdd::addAllowedMethods;
	myMap["index"] = &ConfigAdd::addIndex;
	myMap["autoindex"] = &ConfigAdd::addAutoIndex;
	myMap["location"] = &ConfigAdd::addLocation;
	// myMap["cgi_param"] = &ConfigAdd::addCGIParam;
	// myMap["cgi_pass"] = &ConfigAdd::addCGIPass;
	return (myMap);
}

void	ConfigServer::parseServer(fileVector file, size_t *index) {
	fileVector			args;
	std::string			directive;
	
	while (++(*index) < file.size())
	{
		std::cout << file[*index] << std::endl;
		if (this->_serverParsingMap.find(file[*index]) != this->_serverParsingMap.end()) {
			if (!directive.empty()) {
				this->_serverParsingMap[directive](this, args);
				args.clear();
			}
			directive = file[(*index)];
		}
		else if (file[*index] == "}") {
			try {
				if (!args.empty())
					this->_serverParsingMap[directive](this, args);
				break ;
			}
			catch (const std::exception &e) {
				std::cerr << RED << e.what() << RESET << std::endl;
				return ;
			}
		}
		else {
			args.push_back(file[*index]);
		}
	}
}

//SET
void	ConfigServer::setListen(std::vector<t_listen> listen) {this->_listen = listen;}
void	ConfigServer::setRoot(std::string root) {this->_root = root;}
void	ConfigServer::setServerName(std::vector<std::string> serverName) {this->_server_name = serverName;}
void	ConfigServer::setErrorPages(std::map<int, std::string> errorPages) {this->_error_pages = errorPages;}
void	ConfigServer::setBufferSize(int bufferSize) {this->_client_body_buffer_size = bufferSize;}
void	ConfigServer::setAllowedMethods(std::set<std::string> methods) {this->_allowed_methods = methods;}
void	ConfigServer::setIndex(std::vector<std::string> index) {this->_index = index;}
void	ConfigServer::setAutoIndex(bool autoIndex) {this->_autoindex = autoIndex;}
void	ConfigServer::setLocation(std::map<std::string, ConfigServer> location) {this->_location = location;}

//GET
const std::vector<t_listen>					&ConfigServer::getListen(void) const {return (this->_listen);}
const std::string							&ConfigServer::getRoot(void) const {return (this->_root);}
const std::vector<std::string>				&ConfigServer::getServerName(void) const {return (this->_server_name);}
const std::map<int, std::string>			&ConfigServer::getErrorPages(void) const {return (this->_error_pages);}
const int									&ConfigServer::getBufferSize(void) const {return (this->_client_body_buffer_size);}
const std::set<std::string>					&ConfigServer::getAllowedMethods(void) const {return (this->_allowed_methods);}
const std::vector<std::string>				&ConfigServer::getIndex(void) const {return (this->_index);}
const bool									&ConfigServer::getAutoIndex(void) const {return (this->_autoindex);}
const std::map<std::string, ConfigServer>	&ConfigServer::getLocation(void) const {return (this->_location);}

//STREAM
std::ostream	&operator<<(std::ostream &out, const ConfigServer &server) {
	out << "================================================" << std::endl;
	out << "server_name: ";
	for (size_t i = 0; i < server._server_name.size(); i++)
		out << server._server_name[i] << " ";
	out << std::endl;

	out << "Listen:" << std::endl;
	for (size_t i = 0; i < server._listen.size(); i++)
		out << "\t" << std::hex << server._listen[i].host << ":" << std::dec << server._listen[i].port << std::endl;
	
	out << "error_page:" << std::endl;
	for (std::map<int, std::string>::const_iterator i = server._error_pages.begin(); i != server._error_pages.end(); i++) {
		out << "\t" << i->first << " " << i->second << std::endl;
	}
	
	out << "allowed methods: ";
	for (std::set<std::string>::iterator i = server._allowed_methods.begin(); i != server._allowed_methods.end(); i++)
		out << " " << *i;
	out << std::endl;
	
	out << "root: " << server._root << std::endl;
	
	out << "client_body_buffer_size: " << server._client_body_buffer_size << std::endl;
	
	out << "autoindex: " << (server._autoindex ? "on" : "off") << std::endl;
	
	out << "index: ";
	for (fileVector::const_iterator i = server._index.begin(); i != server._index.end(); i++)
		out << *i << " ";
	out << std::endl;
	
	// out << "alias: " << server._alias << std::endl;
	// for (std::map<std::string, ConfigServer>::const_iterator i = server._location.begin(); i != server._location.end(); i++) {
	// 	out << std::endl << "LOCATION " << i->first << std::endl;
	// 	out << i->second << std::endl;
	// }
	
	// out << "cgi_param:" << std::endl;
	// for (std::map<std::string, std::string>::const_iterator i = server._cgi_param.begin(); i != server._cgi_param.end(); i++)
	// 	out << "\t" << i->first << " = " << i->second << std::endl;
	// out << "cgi_pass:	" << server._cgi_pass << std::endl;

	return (out);
}
