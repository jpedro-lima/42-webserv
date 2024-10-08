/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:02:40 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/07 22:02:33 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Webserv.hpp"

class Client {
public:
	~Client(void);
	Client(void);

	
private:
	int			_socket;
	Server		*_server;
	bool		_ready;
	std::string	_request;
	std::string	_response;
};

#endif //CLIENT_HPP