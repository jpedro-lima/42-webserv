/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 03:07:52 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "RequestConfig.hpp"
# include "Response.hpp"

typedef struct s_listen	t_listen;
struct					sockaddr_in;

class Server {
public:
	~Server(void);
	Server(void);
	Server(t_listen listen);

	void	setup(void);
	void	readClientRequest(int socket);
	void	processRequest(int socket, Config *conf);
	void	processChunk(int socket);
	void	sendResponse(int socket);

	void	close(int socket);
	void	clear(void);

	int			getFd(void) const;
	sockaddr_in	getSockAddr(void) const;

	void	setRequest(std::pair<int, std::string> newRequest);

private:
	std::map<int, std::string>	_requests;
	t_listen					_listen;
	int							_fd;
	sockaddr_in					_addr;
};

#endif //SERVER_HPP