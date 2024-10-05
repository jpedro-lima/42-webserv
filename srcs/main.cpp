/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:56:13 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/04 23:07:14 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "Service.hpp"

int main(int argc, const char **argv) {
	if (argc != 2) {
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return (1);
	}
	try {
		Service	service;
		service.config(argv[1])
			   .setup()
			   .run()
			   .clear();
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}