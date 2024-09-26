/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigArgs.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:20:09 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/26 14:51:20 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGARGS_HPP
# define CONFIGARGS_HPP

# include "Webserv.hpp"

typedef struct	s_listen	t_listen;
class ConfigServer;

namespace ConfigDefault {
	std::map<int, std::string>	defaultErrorPages(void);
	t_listen					defaultListen(void);
	std::set<std::string>		defaultAllowMethods(void);
};

namespace ConfigAdd {
	void	listen(ConfigServer *server, fileVector args);
	void	root(ConfigServer *server, fileVector args);
	void	serverName(ConfigServer *server, fileVector args);
	void	errorPages(ConfigServer *server, fileVector args);
	void	clientBodyBufferSize(ConfigServer *server, fileVector args);
	void	allowedMethods(ConfigServer *server, fileVector args);
	void	index(ConfigServer *server, fileVector args);
	void	autoIndex(ConfigServer *server, fileVector args);
	void	location(ConfigServer *server, fileVector args);
//	void	cgiParam(ConfigServer *server, fileVector args);
//	void	cgiPass(ConfigServer *server, fileVector args);
};

#endif //CONFIGARGS_HPP