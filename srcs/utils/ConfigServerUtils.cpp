/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:02:53 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/03 17:45:02 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServerUtils.hpp"

namespace ConfigDefault {

	std::map<int, std::string>	defaultErrorPages(void) {
		std::map<int, std::string> errorPages;
		errorPages[400] = "./400.html";
		errorPages[403] = "./403.html";
		errorPages[404] = "./404.html";
		errorPages[405] = "./405.html";
		errorPages[410] = "./410.html";
		errorPages[413] = "./413.html";
		errorPages[500] = "./500.html";
		return (errorPages);
	}

	t_listen	defaultListen(void) {
		t_listen listen;
		listen.port = 80;
		listen.host = "";
		return (listen);
	}

	std::set<std::string>	defaultAllowMethods(void) {
		std::set<std::string> methods;
		methods.insert("GET");
		methods.insert("POST");
		methods.insert("DELETE");
		methods.insert("HEAD");
		methods.insert("PUT");
		methods.insert("OPTIONS");
		methods.insert("TRACE");
		methods.insert("PATCH");
		return (methods);
	}
}

namespace ConfigAdd {

	void	addListen(ConfigServer *server, fileVector args){
		if (args.empty() || args.size() > 1)
			throw Exceptions::ExceptionInvalidListenArgs();

		t_listen temp = ConfigDefault::defaultListen();
		size_t sep = args[0].find(":");
		if(sep != std::string::npos) {
			temp.host = args[0].substr(0, sep);
			temp.port = std::atoi((args[0].substr(sep + 1, args[0].length()).c_str()));
		} else {
			temp.port = 80;
			if (args[0].find(".") != std::string::npos || args[0] == "localhost")
				temp.host = args[0];
			else
				temp.port = std::atoi(args[0].c_str());
		}
		if (temp.host.empty())
			temp.host = "0.0.0.0";
		if(temp.host == "localhost")
			temp.host = LOCALHOST;
		std::vector<t_listen> listen = server->getListen();
		for (std::vector<t_listen>::iterator i = listen.begin(); i != listen.end(); i++) {
			if (i->host == temp.host && i->port == temp.port)
				throw Exceptions::ExceptionInvalidListenArgs();
		}
		listen.push_back(temp);
		server->setListen(listen);
	}

	void	addRoot(ConfigServer *server, fileVector args){
		if (args.empty() || server->getRoot() != "")
			throw Exceptions::ExceptionInvalidRootArgs();
		server->setRoot(args[0]);
	}

	void	addServerName(ConfigServer *server, fileVector args){
		std::vector<std::string> serverName;

		if (args.empty())
			throw Exceptions::ExceptionInvalidServerName();
		for (size_t i = 0; i < args.size(); i++)
			serverName.push_back(args[i]);
		server->setServerName(serverName);
	}

	void	addErrorPages(ConfigServer *server, fileVector args){
		if (args.empty() || args.size() > 2
			|| !Utils::isdigit(args[0]) || access(args[1].c_str(), F_OK ) == -1)
			throw Exceptions::ExceptionInvalidErrorPageArgs();
		std::map<int, std::string> error_page = server->getErrorPages();
		error_page[std::atoi(args[0].c_str())] = args[1];
		server->setErrorPages(error_page);
	}

	void	addClientBodyBufferSize(ConfigServer *server, fileVector args){
		if (args.empty() || server->getBufferSize() != 10000000 
			|| args.size() > 1 || !Utils::isdigit(args[0]) )
			throw Exceptions::ExceptionInvalidClientBodyBufferSize();
		server->setBufferSize(std::atoi(args[0].c_str()));
	}

	void	addAllowedMethods(ConfigServer *server, fileVector args){
		std::string methods[] = {"GET", "POST", "DELETE", "HEAD", "PUT", "OPTIONS", "TRACE", "PATCH"};
		std::set<std::string> allowedMethods;

		if (args.empty())
			throw Exceptions::ExceptionInvalidAllowMethod();
		for (fileVector::iterator itr = args.begin(); itr != args.end(); itr++) {
			bool found = false;
			for (size_t i = 0; i < sizeof(methods)/sizeof(methods[0]); i++) {	
				if (*itr == methods[i])
					found = true;
			}
			if (found)
				allowedMethods.insert(*itr);
			else
				throw Exceptions::ExceptionInvalidAllowMethod();
		}
		server->setAllowedMethods(allowedMethods);
	}

	void	addIndex(ConfigServer *server, fileVector args){
		std::vector<std::string> index;

		if (args.empty())
			throw Exceptions::ExceptionInvalidIndexArgs();
		for (size_t i = 0; i < args.size(); i++)
			index.push_back(args[i]);
		server->setIndex(index);
	}

	void	addAutoIndex(ConfigServer *server, fileVector args){
		if (args.empty() || args.size() > 1)
			throw Exceptions::ExceptionInvalidAutoIndex();
		if (args[0] == "on" || args[0] == "true")
			server->setAutoIndex(true);
		else if (args[0] == "off" || args[0] == "false")
			server->setAutoIndex(false);
		else
			throw Exceptions::ExceptionInvalidAutoIndex();
	}

	void	addLocation(ConfigServer *server, fileVector args){
		std::string							locationPath;
		fileVector							locationArgs;
		std::string							directive;
		parseMap							locationParsingMap;
		ConfigServer						temp;

		locationParsingMap = server->getServerParsingMap();
		if (args[1] != "{")
			throw Exceptions::ExceptionInvalidLocationMethod();
		try {
			for (size_t index = 0; index < args.size(); index++)
			{
				if (locationParsingMap.find(args[index]) != locationParsingMap.end()) {
					if (!directive.empty()) {
						locationParsingMap[directive](&temp, locationArgs);
						locationArgs.clear();
					}
					directive = args[index];
				}
				else if (args[index] == "}") {
					if (directive.empty())
						throw Exceptions::ExceptionInvalidLocationMethod();
					if (!locationArgs.empty())
						locationParsingMap[directive](&temp, locationArgs);
					break ;
				} 
				else
					locationArgs.push_back(args[index]);
			}
		} catch (const std::exception &e) {
			throw ;
		}
		std::map<std::string, ConfigServer>	location = server->getLocation();
		location[args[0]] = temp;
		server->setLocation(location);
	}
}