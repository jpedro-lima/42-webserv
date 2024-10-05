/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:30 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/05 02:54:14 by joapedr2         ###   ########.fr       */
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
	FD_ZERO(&_read);
	std::vector<t_listen>	listens = this->_config.getAllListens();
	std::vector<t_listen>::iterator lstn;
	for (lstn = listens.begin() ; lstn != listens.end() ; lstn++) {
		std::cout << "---------------------------------------" << std::endl;
		std::cout <<GREY<< "\tSetting up " <<BLUE<< lstn->host
			<<GREY<<":" <<BLUE<< lstn->port <<GREY<< "..." <<RESET<< std::endl;
		try {
			Server server(*lstn);
			server.setup();
			int fd = server.getFd();
			FD_SET(fd, &_read);
			this->_servers.insert(std::make_pair(fd, server));
			if (fd > this->_max_fd)
				this->_max_fd = fd;
			if (this->_max_fd == 0)
				throw Exceptions::ExceptionServiceServer();
		}
		catch (const std::exception&) {
			throw ;
		}
	}
}

void	Service::run(void) {
	fd_set	read_cur;
	fd_set	write_cur;

	FD_ZERO(&read_cur);
	FD_ZERO(&write_cur);
	std::cout << "---------------------------------------" << std::endl;
	std::cout << GREEN << "\t Waiting for activity... " << RESET << std::endl;
	while (true)
	{
		Service::_synchronize(&read_cur, &write_cur);
		if (select(this->_max_fd, &this->_read, &this->_write, 0, 0) == -1) {
			FD_ZERO(&this->_read);
			FD_ZERO(&this->_write);
			continue ;
		}
		
	}
	std::cout << "Wow RUNNING" << std::endl;
}

void	Service::clear(void) {
//	std::map<int, Server>::iterator server;
//	for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
//		server->second.clear();
//	}
	std::cout << "clear" << std::endl;
//	this->_servers.clear();
}

void	Service::_synchronize(fd_set *read_current, fd_set *write_current) {
	*read_current = this->_read;
	*write_current = this->_write;

	std::map<int, Server>::iterator server;
	for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
		FD_SET(server->first, read_current);
	}
	// FD_ZERO(write_current);
	// memcpy(read_current, &this->_read, sizeof(this->_read));
}

//GET
const Config	&Service::getConfig(void) const {return (this->_config);}