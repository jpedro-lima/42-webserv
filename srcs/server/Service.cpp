/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:30 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/04 23:07:02 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Service.hpp"

Service::~Service(void) {}

Service::Service(void) {}

Service&	Service::config(const char *filePath) {
	Config temp(filePath);
	this->_config = temp;

	return *this;
}

Service&	Service::setup(void) {
	std::vector<t_listen>	listens = this->_config.getAllListens();

	FD_ZERO(&_fd_set);
	this->_fd_size = listens.size();
	this->_max_fd = 0;
	std::vector<t_listen>::iterator lstn;
	for (lstn = listens.begin() ; lstn != listens.end() ; lstn++)
	{
		Server	server(*lstn);
		server.setup();
		int fd = server.getFd();
		FD_SET(fd, &_fd_set);
		this->_servers.insert(std::make_pair(fd, server));
		if (fd > _max_fd)
			_max_fd = fd;
		std::cout << "---------------------------------------" << std::endl;
		std::cout <<GREY<< "\tSetting up " <<BLUE<< lstn->host
			<<GREY<<":" <<BLUE<< lstn->port <<GREY<< "..." <<RESET<< std::endl;
	}
	if (_max_fd == 0)
		throw Exceptions::ExceptionServiceServer();

	return *this;
}

Service&	Service::run(void) {
	std::cout << "Wow RUNNING" << std::endl;

	return *this;
}

Service&	Service::clear(void) {
	std::cout << "Wow Cleanning" << std::endl;

	return *this;
}

//GET
const Config	&Service::getConfig(void) const {return (this->_config);}