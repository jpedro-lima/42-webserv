/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:30 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/03 17:50:08 by joapedr2         ###   ########.fr       */
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
		std::cout << "--------------------------------" << std::endl;
		std::cout <<GREY<< "\tSetting up " <<BLUE<< lstn->host
			<<GREY<<":" <<BLUE<< lstn->port <<GREY<< "..." <<RESET<< std::endl;
	}
	if (_max_fd == 0)
		throw Exceptions::ExceptionServiceServer();
}

void	Service::run(void) {
	std::cout << "Wow RUNNING" << std::endl;
}

void	Service::clear(void) {
	std::cout << "Wow Cleanning" << std::endl;
}

//GET
const Config	&Service::getConfig(void) const {return (this->_config);}