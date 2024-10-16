/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexGenerator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:37:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/11 08:58:34 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEXGENERATOR_HPP
# define AUTOINDEXGENERATOR_HPP

# include "Webserv.hpp"

class AutoIndexGenerator {
public:
	~AutoIndexGenerator(void);
	AutoIndexGenerator(void);
	AutoIndexGenerator(AutoIndexGenerator const &src);

	static std::string  getPage(const char *path, std::string const &host, int port);
private:
	static std::string  getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port);

};

#endif //AUTOINDEXGENERATOR_HPP
