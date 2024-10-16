/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:02:53 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 22:20:44 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

namespace ConfigDefault {

	std::map<int, std::string>	defaultErrorPages(void) {
		std::map<int, std::string> errorPages;
		errorPages[400] = "./default/error_pages/400.html";
		errorPages[403] = "./default/error_pages/403.html";
		errorPages[404] = "./default/error_pages/404.html";
		errorPages[405] = "./default/error_pages/405.html";
		errorPages[410] = "./default/error_pages/410.html";
		errorPages[413] = "./default/error_pages/413.html";
		errorPages[500] = "./default/error_pages/500.html";
		return (errorPages);
	}

	t_listen	defaultListen(void) {
		t_listen listen;
		listen.port = 80;
		listen.host = "0.0.0.0";
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
			if (args[0].find(".") != std::string::npos || args[0] == "localhost")
				temp.host = args[0];
			else
				temp.port = std::atoi(args[0].c_str());
		}
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
		DIR *dir;
		if (args.empty() || args.size() != 1
			|| (dir = opendir (args[0].c_str())) == NULL)
			throw Exceptions::ExceptionInvalidErrorPageArgs();

    	struct dirent *ent;
		std::map<int, std::string> error_page = server->getErrorPages();
		while ((ent = readdir (dir)) != NULL) {
			std::string file = std::string(ent->d_name);
			std::string code = file.substr(0, file.find_first_of("."));
			if (Utils::isdigit(code))
				error_page[atoi(code.c_str())] = args[0] + file;
		}
    	closedir (dir);
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
		ConfigServer						temp(server);
	
		locationParsingMap = server->getServerParsingMap();
		if (args[1] != "{")
			throw Exceptions::ExceptionInvalidLocationMethod();
		try {
			for (size_t index = 2; index < args.size(); index++)
			{
				if (locationParsingMap.find(args[index]) != locationParsingMap.end()) {
					if (!directive.empty()) {
						locationParsingMap[directive](&temp, locationArgs);
						locationArgs.clear();
					}
					directive = args[index];
					if (directive == "location") {
						while (args[++index] != "}")
							locationArgs.push_back(args[index]);
						locationArgs.push_back(args[index]);
						locationParsingMap[directive](&temp, locationArgs);
					}
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
		} catch (const std::exception &e) {throw ;}
		std::map<std::string, ConfigServer>	location = server->getLocation();
		location[args[0]] = temp;
		server->setLocation(location);
	}

	void	addCGIParam(ConfigServer *server, fileVector args) {
		if (args.size() != 2)
			throw Exceptions::ExceptionInvalidCGIParamArgs();
		std::map<std::string, std::string> temp;
		temp[args[0]] = args[1];
		server->setCGIParam(temp);
	}
	
	void	addCGIPass(ConfigServer *server, fileVector args) {
		if (args.size() != 1)
			throw Exceptions::ExceptionInvalidCGIPassArgs();
		server->setCGIPass(args[0]);
	}

}
