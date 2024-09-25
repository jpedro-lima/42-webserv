/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/25 17:46:44 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::~ConfigServer() {};

ConfigServer::ConfigServer(void){
	this->_listen.clear();
	this->_listen.clear();
	this->_root.clear();
	this->_index.clear();
	this->_server_name.clear();
	this->_error_pages.clear();
	this->_client_body_buffer_size = 10000000;
	this->_allowed_methods.clear();
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
	myMap["error_page"] = &ConfigServer::grapErrorPages;
	myMap["client_body_buffer_size"] = &ConfigServer::grapClientBodyBufferSize;
	// myMap["cgi_param"] = &ConfigServer::grapCgiParam;
	// myMap["cgi_pass"] = &ConfigServer::grapCgiPass;
	myMap["allow_methods"] = &ConfigServer::grapAllowedMethods;
	myMap["index"] = &ConfigServer::grapIndex;
	myMap["autoindex"] = &ConfigServer::grapAutoIndex;
	myMap["location"] = &ConfigServer::grapLocation;
	return (myMap);
}

void	ConfigServer::parseServer(fileVector file, size_t *index) {
	fileVector			args;
	std::string			directive;
	
	while (++(*index) < file.size())
	{
		if (this->_serverParsingMap.find(file[*index]) != this->_serverParsingMap.end()) {
			if (!directive.empty()) {
				(this->*(_serverParsingMap)[directive])(args);
				args.clear();
			}
			directive = file[(*index)];
		}
		else if (file[*index] == "}") {
			try {
				if (!args.empty())
					(this->*(_serverParsingMap)[directive])(args);
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

void	ConfigServer::grapListen(fileVector args){
	std::cout << "grapListen" << std::endl;
	(void)args;
}

void	ConfigServer::grapRoot(fileVector args){
	std::cout << "grapRoot" << std::endl;
	(void)args;
}

void	ConfigServer::grapServerName(fileVector args){
	if (args.empty())
		throw Exceptions::ExceptionInvalidServerName();
	for (size_t i = 0; i < args.size(); i++)
		this->_server_name.push_back(args[i]);
}

void	ConfigServer::grapErrorPages(fileVector args){
	std::cout << "grapErrorPages" << std::endl;
	(void)args;
}

void	ConfigServer::grapClientBodyBufferSize(fileVector args){
	std::cout << "grapClienteBodyBuffer" << std::endl;
	(void)args;
}

void	ConfigServer::grapAllowedMethods(fileVector args){
	std::string methods[] = {"GET", "POST", "DELETE", "HEAD", "PUT", "OPTIONS", "TRACE", "PATCH"};
	if (args.empty())
		throw Exceptions::ExceptionInvalidAllowMethod();
	this->_allowed_methods.clear();
	for (fileVector::iterator itr = args.begin(); itr != args.end(); itr++) {
		bool found = false;
		for (size_t i = 0; i < sizeof(methods)/sizeof(methods[0]); i++) {	
			if (*itr == methods[i])
				found = true;
		}
		if (found)
			this->_allowed_methods.insert(*itr);
		else
			throw Exceptions::ExceptionInvalidAllowMethod();
	}
}

void	ConfigServer::grapIndex(fileVector args){
	std::cout << "grapIndex" << std::endl;
	(void)args;
}

void	ConfigServer::grapAutoIndex(fileVector args){
	std::cout << "grapAutoIndex" << std::endl;
	(void)args;
}

void	ConfigServer::grapLocation(fileVector args){
	std::cout << "grapLocation" << std::endl;
	(void)args;
}
