/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/03 22:49:56 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::~Server(void) {}

Server::Server(void) {}

Server::Server(t_listen listen) {
	this->_requests.clear();
	this->_fd = 0;
	this->_listen = listen;
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_listen.port);
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	if (this->_listen.host != "0.0.0.0" )
		this->_addr.sin_addr.s_addr = inet_addr(this->_listen.host.c_str());
}

void	Server::setup(void)
{
	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw Exceptions::ExceptionServerSocket();
	if (bind(this->_fd, (struct sockaddr*)&this->_addr, sizeof(this->_addr)) == -1)
		throw Exceptions::ExceptionServerBind();
	if (listen(this->_fd, 1000) == -1)
		throw Exceptions::ExceptionServerListen();
}

//GET
int	Server::getFd(void) const {return(this->_fd);}
