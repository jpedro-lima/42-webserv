/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:30 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 14:07:05 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Service.hpp"

Service::~Service(void) {}

Service::Service(void) {}

void	Service::config(const char *filePath) {
	Config temp(filePath);
	this->_config = temp;
}

void	Service::setup(void) {
	FD_ZERO(&this->_read);
	std::vector<t_listen>	listens = this->_config.getAllListens();
	std::vector<t_listen>::iterator lstn;
	for (lstn = listens.begin() ; lstn != listens.end() ; lstn++) {
		std::cout <<GREY<< "\tSetting up " <<BLUE<< lstn->host
			<<GREY<<":" <<BLUE<< lstn->port <<RESET<< std::endl;
		try {
			Server server(*lstn);
			server.setup();
			int fd = server.getFd();
			FD_SET(fd, &this->_read);
			this->_servers.insert(std::make_pair(fd, server));
			this->updateMaxFd(fd);
			if (this->_max_fd == 0)
				throw Exceptions::ExceptionServiceServer();
		}
		catch (const std::exception&) {
			throw ;
		}
	}
}

void	Service::run(void) {
	fd_set	read_current;
	fd_set	write_current;
	struct timeval	timeout;

	FD_ZERO(&read_current);
	FD_ZERO(&write_current);
	std::cout << "---------------------------------------" << std::endl;
	std::cout << GREEN << "\t Waiting for activity... " << RESET << std::endl;
	while (true)
	{
		int ret = 0;
		while (ret == 0)
		{
			timeout.tv_sec  = 1;
			timeout.tv_usec = 0;

			this->_synchronize(&read_current, &write_current);
			ret = select(this->_max_fd + 1, &read_current, &write_current, NULL, &timeout);
			if (ret == -1) {
				std::cerr << RED << "Problem with select!" << RESET << std::endl;
				FD_ZERO(&this->_read);
				this->setDefaultReadServers();
				ret = 0;
			}
		}
		// Send Response
		std::vector<t_client>::iterator client;
		for (client = this->_clients.begin(); client != this->_clients.end(); client++) {
			try {
				if (FD_ISSET(client->socket, &write_current) && client->ready) {
					client->server->sendResponse(client->socket);
					FD_CLR(client->socket, &this->_read);
					close(client->socket);
					this->_clients.erase(client);
					break ;
				}
			} catch (const std::exception&) {
				FD_CLR(client->socket, &this->_read);
				FD_CLR(client->socket, &read_current);
				this->_clients.erase(client);
				break ;
			}
		}
		// Read and Process the Request
		for (client = this->_clients.begin(); client != this->_clients.end(); client++) {
			try {
				if (FD_ISSET(client->socket, &this->_read)) {
					client->server->readClientRequest(client->socket);
					client->server->processRequest(client->socket, &this->_config);
					client->ready = true;
				}
			} catch (const std::exception&) {
				FD_CLR(client->socket, &this->_read);
				this->_clients.erase(client);
				break ;
			}
		}
		//Accept Request
		std::map<int, Server>::iterator server;
		for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
			if (FD_ISSET(server->first, &read_current)) {
				int	cSocket = accept(server->first, NULL, NULL);
				server->second.setRequest(std::make_pair(cSocket, ""));
				if (cSocket > 0) {
					FD_SET(cSocket, &this->_read);
					t_client temp;
					temp.socket = cSocket;
					temp.server = &server->second;
					temp.ready = false;
					this->_clients.push_back(temp);
					this->updateMaxFd(cSocket);
				}
			}	
		}
	}
}

void	Service::_synchronize(fd_set *read_current, fd_set *write_current) {
	FD_ZERO(read_current);
	FD_ZERO(write_current);
	memcpy(read_current, &this->_read, sizeof(this->_read));
	std::vector<t_client>::iterator client;
	for (client = this->_clients.begin(); client != this->_clients.end(); client++)
		FD_SET(client->socket, write_current);
}

void	Service::clear(void) {
	std::map<int, Server>::iterator server;
	for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
		server->second.clear();
	}
	this->_servers.clear();
	this->_clients.clear();
}

//SET
void	Service::setMaxFd(int fd) {this->_max_fd = fd;}

//GET
Config	Service::getConfig(void) const {return (this->_config);}
int		Service::getMaxFd(void) const {return (this->_max_fd);}
