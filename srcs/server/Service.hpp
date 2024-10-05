/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Service.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:33 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/02 08:44:28 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVICE_HPP
# define SERVICE_HPP

# include "Webserv.hpp"
# include "Config.hpp"
# include "Server.hpp"

#include <stdio.h>
#include <string.h>

class Service {
public:
	~Service(void);
	Service(void);

	void	config(const char *filePath);
	void	setup(void);
	void	run(void);
	void	clear(void);

	const Config	&getConfig(void) const;
private:

	Config					_config;
	std::map<int, Server>	_servers;
	std::map<int, Server*>	_sockets;
	std::vector<int>		_ready;
	int						_max_fd;
	unsigned int			_fd_size;
	fd_set					_write;
	fd_set					_read;

	void	_synchronize(fd_set *read_current, fd_set *write_current);

};

#endif //SERVICE_HPP
