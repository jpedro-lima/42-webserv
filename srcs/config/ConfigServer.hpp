/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/25 16:54:24 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

# include "Webserv.hpp"

typedef	std::vector<std::string>	fileVector;
# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>


typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;

class ConfigServer {
public:
	~ConfigServer(void);
	ConfigServer(void);
	
	void    parseServer(fileVector file, size_t *index);

	void	grapListen(std::vector<std::string> args);
	void	grapRoot(std::vector<std::string> args);
	void	grapServerName(std::vector<std::string> args);
	void	grapErrorPages(std::vector<std::string> args);
	void	grapClientBodyBufferSize(std::vector<std::string> args);
	void	grapAllowedMethods(std::vector<std::string> args);
	void	grapIndex(std::vector<std::string> args);
	void	grapAutoIndex(std::vector<std::string> args);
	void	grapLocation(std::vector<std::string> args);
//	void	grapCGIParam(std::vector<std::string> args);
//	void	grapCGIPass(std::vector<std::string> args);

private:
	std::string	_serverText;

	parseMap	_serverParsingMap;
	parseMap	_locationParsingMap;

	std::vector<t_listen>				_listen;
	std::string							_root;
	std::vector<std::string>			_server_name;
	std::map<int, std::string>			_error_pages;
	int									_client_body_buffer_size;
	std::set<std::string>				_allowed_methods;
	std::vector<std::string>			_index;
	bool								_autoindex;
	std::map<std::string, ConfigServer>	_location;

	parseMap _initParseMap();
};

#endif //CONFIGSERVER_HPP