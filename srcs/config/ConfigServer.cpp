/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 20:42:36 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::~ConfigServer() {};

ConfigServer::ConfigServer(fileVector file){
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

	setNewServerConfig(file);
}
