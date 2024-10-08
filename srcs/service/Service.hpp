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

typedef struct	s_client {
	int		socket;
	Server	*server;
	bool	ready;
}				t_client;

class Service {
public:
	~Service(void);
	Service(void);

	void	config(const char *filePath);
	void	setup(void);
	void	run(void);
	void	clear(void);

	//SET
	void	setMaxFd(int fd);

	//GET
	Config	getConfig(void) const;
	int		getMaxFd(void) const;

	//Utils
	void	updateMaxFd(int fd);
	void	setDefaultReadServers(void);

private:

	Config					_config;
	std::map<int, Server>	_servers;
	std::vector<t_client>	_clients;

	int				_max_fd;
	unsigned int	_fd_size;
	fd_set			_read;
	fd_set			_write;

	void	_synchronize(fd_set *read_current, fd_set *write_current);

};

#endif //SERVICE_HPP
