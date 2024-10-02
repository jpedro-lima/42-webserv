/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:06:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/02 11:00:24 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "Webserv.hpp"
# include "ConfigServer.hpp"

typedef struct	s_listen	t_listen;

class Config {
public:
	~Config(void);
	Config(void);
	Config(const char *configPath);

	std::vector<ConfigServer>	getServers(void) const;
	std::vector<t_listen>		getAllListens(void) const;

	Config	*operator=(const Config *config);
private:
	std::string					_configText;
	fileVector					_fileVector;
	std::vector<ConfigServer>	_servers;
	
	void	parser(fileVector file);
	void	checkServers(void);
};

#endif //CONFIG_H
