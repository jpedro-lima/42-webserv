/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:56:13 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/05 02:34:22 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "Service.hpp"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		std::cout << BLUE << "\n\t Stopping server..." << RESET << std::endl;
		exit(0);
	}
}

int main(int argc, const char **argv) {
	if (argc != 2) {
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return (1);
	}
	try {
		signal(SIGINT, signal_handler);
		Service	service;
		service.config(argv[1]);
		service.setup();
		service.run();
		service.clear();
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}