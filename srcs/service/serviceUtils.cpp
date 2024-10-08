/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serviceUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:37:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/07 11:31:34 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Service.hpp"

void	Service::updateMaxFd(int fd) {
	if (this->_max_fd < fd)
		this->_max_fd = fd;
}

void	Service::setDefaultReadServers() {
	FD_ZERO(&this->_read);
	std::map<int, Server>::iterator server;
	for (server = this->_servers.begin(); server != this->_servers.end(); server++) {
		FD_SET(server->first, &this->_read);
		this->updateMaxFd(server->first);
		if (this->_max_fd == 0)
			throw Exceptions::ExceptionServiceServer();
	}
}

