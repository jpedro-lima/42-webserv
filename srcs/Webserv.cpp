/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:56:13 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 16:50:25 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

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
			std::string teste = FileReader::readFile(argv[1]);
			FileReader::checkerConfigFile(teste);

			fileVector fileTest = FileReader::split(teste, " \f\n\r\t\v");

			std::cout << teste << std::endl;
			for (size_t i = 0; i < fileTest.size(); i++)
				std::cout << fileTest[i] << std::endl;
		}
		catch (const std::exception &e) {
			std::cerr << RED << e.what() << RESET << std::endl;	
		}

	}
	else
	{
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return (1);
	}
	return 0;
}