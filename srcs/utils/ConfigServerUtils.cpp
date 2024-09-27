/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:02:53 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/27 17:05:39 by joapedr2         ###   ########.fr       */
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
		listen.host = LOCALHOST;
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

		t_listen temp;
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
		if(temp.host == "localhost")
			temp.host = LOCALHOST;
		std::vector<t_listen> listen = server->getListen();
		listen.push_back(temp);
		server->setListen(listen);
	}

	void	addRoot(ConfigServer *server, fileVector args){
		std::cout << "grapRoot" << std::endl;
		(void)args;
		(void)server;
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
		std::cout << "grapErrorPages" << std::endl;
		(void)args;
		(void)server;
	}

	void	addClientBodyBufferSize(ConfigServer *server, fileVector args){
		std::cout << "grapClienteBodyBuffer" << std::endl;
		(void)args;
		(void)server;
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
		std::cout << "grapIndex" << std::endl;
		(void)args;
		(void)server;
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
		std::cout << "grapLocation" << std::endl;
		(void)args;
		(void)server;
	}
}