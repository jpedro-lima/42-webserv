/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:09:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/27 12:50:46 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

# include "Webserv.hpp"
# include "ConfigServerUtils.hpp"

typedef	std::vector<std::string>	fileVector;
typedef struct	s_listen			t_listen;

# define parseMap std::map<std::string, void (*)(ConfigServer *, fileVector)>

class ConfigServer {
public:
	~ConfigServer(void);
	ConfigServer(void);
	
	void    parseServer(fileVector file, size_t *index);

//SET
	void	setListen(std::vector<t_listen> listen);
	void	setRoot(std::string root);
	void	setServerName(std::vector<std::string> serverName);
	void	setErrorPages(std::map<int, std::string> errorPages);
	void	setBufferSize(int bufferSize);
	void	setAllowedMethods(std::set<std::string> methods);
	void	setIndex(std::vector<std::string> index);
	void	setAutoIndex(bool autoIndex);
	void	setLocation(std::map<std::string, ConfigServer> location);
//GET
	const std::vector<t_listen>					&getListen(void) const;
	const std::string							&getRoot(void) const;
	const std::vector<std::string>				&getServerName(void) const;
	const std::map<int, std::string>			&getErrorPages(void) const;
	const int									&getBufferSize(void) const;
	const std::set<std::string>					&getAllowedMethods(void) const;
	const std::vector<std::string>				&getIndex(void) const;
	const bool									&getAutoIndex(void) const;
	const std::map<std::string, ConfigServer>	&getLocation(void) const;

//STREAM
	friend std::ostream	&operator<<(std::ostream &out, const ConfigServer &server);

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