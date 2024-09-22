/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 20:09:29 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

# include "Webserv.hpp"

typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;

class ConfigServer {
public:
	~ConfigServer(void);
	ConfigServer(fileVector file);
	
	fileVector	parseServer(const std::string configText);

	// std::string	grapServers(const std::string configText);
	// void	grapListen(const std::string configText);
	// void	grapRoot(const std::string configText);
	// void	grapServerName(const std::string configText);
	// void	grapErrorPages(const std::string configText);
	// void	grapClienteBodyBuffer(const std::string configText);
	// void	grapAllowedMethods(const std::string configText);
	// void	grapIndex(const std::string configText);
	// void	grapAutoIndex(const std::string configText);
	// void	grapLocation(const std::string configText);
//	void	grapCGIParam(const std::string configText);
//	void	grapCGIPass(const std::string configText);

private:
	std::string	_serverText;

	static	parseMap	_serverParsingMap;
	static	parseMap	_locationParsingMap;

	std::vector<t_listen>				_listen;
	std::string							_root;
	std::vector<std::string>			_server_name;
	std::map<int, std::string>			_error_pages;
	int									_client_body_buffer_size;
	std::set<std::string>				_allowed_methods;
	std::vector<std::string>			_index;
	bool								_autoindex;
	std::map<std::string, ConfigServer>	_location;
};

#endif //CONFIGSERVER_HPP