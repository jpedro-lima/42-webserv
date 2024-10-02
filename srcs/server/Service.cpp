/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:30 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/02 14:07:55 by joapedr2         ###   ########.fr       */
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
	_fdSize = listens.size();
	_max_fd = 0;

	for (std::vector<t_listen>::iterator lstn = listens.begin() ; lstn != listens.end() ; lstn++ )
	{
		Server	server(*lstn);
		int		fd;

		server.setup();
	
		fd = serv.getFD();
		FD_SET(fd, &_fd_set);
		_servers.insert(std::make_pair(fd, serv));
		if (fd > _max_fd)
			_max_fd = fd;
		std::cout << "Setting up " << lstn->host << ":" << lstn->port << "..." << std::endl;
	}

	if (_max_fd == 0)
	{
		std::cerr << RED << "Could not setup cluster !" << RESET << std::endl;
		return (-1);
	}
}

//GET
const Config	&Service::getConfig(void) const {return (this->_config);}