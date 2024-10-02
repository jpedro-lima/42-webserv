/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/02 09:23:35 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"

typedef struct s_listen	t_listen;
typedef struct			sockaddr_in;

class Server {
public:
	~Server(void);
	Server(void);
	Server(t_listen listen);

	long	getFD(void);

	int		setup(void);
	void	setAddr(void);
	long	accept(void);
	void	process(long socket, Config & conf);
	void	processChunk(long socket);
	int		recv(long socket);
	int		send(long socket);
	void	close(int socket);
	void	clean(void);

private:
	std::map<long, std::string>	_requests;
	t_listen					_listen;
	int							_fd;
	sockaddr_in					_addr;

};

#endif //SERVER_HPP