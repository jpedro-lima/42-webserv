/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:06:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:37 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H


class Config {
public:
	~Config(void);
	Config(std:string configPath);


private:
	std::string	_configText;
	fileVector	_fileVector;

	std::vector<ConfigServer>	_servers;
};

#endif //CONFIG_H
