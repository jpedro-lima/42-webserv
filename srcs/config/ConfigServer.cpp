/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/23 22:45:49 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::~ConfigServer() {};

ConfigServer::ConfigServer(fileVector file, size_t index){
	this->_listen.port = 80;
	this->_listen.host = LOCALHOST;
	this->_root.clear();
	this->_index.clear();
	this->_server_name = "default";
	this->_error_pages.clear();
	this->_client_body_buffer_size = 10000000;
	this->_allowed_methods = {"GET", "POST", "DELETE", "HEAD" , "PUT", "OPTIONS", "TRACE", "PATCH"};
	this->_autoindex = "off";
	this->_location.clear();
	this->_serverParsingMap = this->_initParseMap();
	this->_locationParsingMap = this->_initParseMap();
}

parseMap ConfigServer::_initParseMap() {
	parseMap	myMap;
	myMap["listen"] = &ConfigServer::grapListen;
	myMap["root"] = &ConfigServer::grapRoot;
	myMap["server_name"] = &ConfigServer::grapServerName;
	myMap["error_page"] = &ConfigServer::grapErrorPage;
	myMap["client_body_buffer_size"] = &ConfigServer::grapClientBodyBufferSize;
	myMap["cgi_param"] = &ConfigServer::grapCgiParam;
	myMap["cgi_pass"] = &ConfigServer::grapCgiPass;
	myMap["allow_methods"] = &ConfigServer::grapAllowedMethods;
	myMap["index"] = &ConfigServer::grapIndex;
	myMap["location"] = &ConfigServer::grapLocation;
	return (myMap);
}

void	ConfigServer::parseServer(size_t &index, fileVector &file) {
	fileVector			args;
	std::string			directive;
	
	while (++index < file.size())
	{
		if (this->_serverParsingMap.find(file[index]) != this->_serverParsingMap.end()) {
			if (!directive.empty()) {
				this->_serverParsingMap[directive](args);
				args.clear();
			}
			directive = file[index];
		}
		else if (file[index] == "}") {
			if (!args.empty())
				this->_serverParsingMap[directive](args);
			break ;	
		}
		else {
			args.push_back(file[index]);
		}
	}
}

void	ConfigServer::grapListen(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapRoot(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapServerName(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapErrorPages(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapClienteBodyBuffer(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapAllowedMethods(fileVector configText){
	if (args.empty())
		throw Exceptions::ExceptionInvalidArguments();
	this->_allowed_methods.clear();
	for (fileVector::iterator i = args.begin(); i != args.end(); i++) {
		this->_allowed_methods.insert(*i);
	}
}

void	ConfigServer::grapIndex(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapAutoIndex(fileVector configText){
	std::cout << "GET" << std::endl;	
}

void	ConfigServer::grapLocation(fileVector configText){
	std::cout << "GET" << std::endl;	
}
