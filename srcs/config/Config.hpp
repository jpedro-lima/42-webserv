/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:06:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 23:15:20 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "Webserv.hpp"
# include "ConfigServer.hpp"
# include "RequestConfig.hpp"

class RequestConfig;

typedef struct	s_listen			t_listen;
typedef	std::vector<std::string>	fileVector;

class Config {
public:
	~Config(void);
	Config(void);
	Config(const char *configPath);

	std::vector<ConfigServer>	getServers(void) const;
	std::vector<t_listen>		getAllListens(void) const;
	
	RequestConfig	getConfigForRequest(t_listen const address, Request &request) const;
	ConfigServer	getServerForRequest(t_listen const address, std::string const hostName) const;


	Config	*operator=(const Config *config);
private:
	std::string					_configText;
	fileVector					_fileVector;
	std::vector<ConfigServer>	_servers;
	
	void	parser(fileVector file);
	void	checkServers(void);
};

#endif //CONFIG_H
