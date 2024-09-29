/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:56:13 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/28 21:44:16 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

class	Config;

int main(int argc, const char **argv) {
	if (argc == 2)
	{
		// Cluster		cluster;

		// try {
		// 	cluster.config(av[1]);
		// 	if (cluster.setup() == -1)
		// 		return (1);
		// 	cluster.run();
		// 	cluster.clean();			
		// }
		// catch (std::exception &e) {
		// 	std::cerr << e.what() << std::endl;
		// }
		try {
			Config config(argv[1]);
			std::vector<ConfigServer> servers = config.getServers();
			for (std::vector<ConfigServer>::iterator i = servers.begin(); i != servers.end(); i++)
				std::cout << *i << std::endl;
		}
		catch (const std::exception &e) {
			std::cerr << RED << e.what() << RESET << std::endl;
			return (1);
		}

	}
	else
	{
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return (1);
	}
	return (0);
}