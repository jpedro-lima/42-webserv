/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/23 22:41:40 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

# include "Webserv.hpp"

# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>

typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;

class ConfigServer {
public:
	~ConfigServer(void);
	ConfigServer(fileVector file, size_t index);
	
	void     ConfigServer::parseServer(size_t &index, fileVector &file);

	void	grapListen(fileVector configText);
	void	grapRoot(fileVector configText);
	void	grapServerName(fileVector configText);
	void	grapErrorPages(fileVector configText);
	void	grapClienteBodyBuffer(fileVector configText);
	void	grapAllowedMethods(fileVector configText);
	void	grapIndex(fileVector configText);
	void	grapAutoIndex(fileVector configText);
	void	grapLocation(fileVector configText);
//	void	grapCGIParam(fileVector configText);
//	void	grapCGIPass(fileVector configText);

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

	std::string methodes[] = {"GET", "POST", "DELETE", "HEAD" , "PUT", "OPTIONS", "TRACE", "PATCH"};
	
};

#endif //CONFIGSERVER_HPP