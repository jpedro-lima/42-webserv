/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:06:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/26 11:37:28 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H


# include "Webserv.hpp"

typedef	std::vector<std::string>	fileVector;

class	ConfigServer;

class Config {
public:
	~Config(void);
	Config(const char *configPath);

	std::vector<ConfigServer>	getServers(void) const;

private:
	std::string					_configText;
	fileVector					_fileVector;
	std::vector<ConfigServer>	_servers;
	
	void	parser(fileVector file);

};

#endif //CONFIG_H
