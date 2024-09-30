/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerUtils.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:20:09 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/29 22:47:55 by joapedr2         ###   ########.fr       */
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
	void	addListen(ConfigServer *server, fileVector args);
	void	addRoot(ConfigServer *server, fileVector args);
	void	addServerName(ConfigServer *server, fileVector args);
	void	addErrorPages(ConfigServer *server, fileVector args);
	void	addClientBodyBufferSize(ConfigServer *server, fileVector args);
	void	addAllowedMethods(ConfigServer *server, fileVector args);
	void	addIndex(ConfigServer *server, fileVector args);
	void	addAutoIndex(ConfigServer *server, fileVector args);
	void	addLocation(ConfigServer *server, fileVector args);
//	void	addCGIParam(ConfigServer *server, fileVector args);
//	void	addCGIPass(ConfigServer *server, fileVector args);
};

#endif //CONFIGARGS_HPP