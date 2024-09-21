/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:36:25 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/19 10:25:54 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileParser.hpp"

FileParser::FileParser(void) {}

FileParser::~FileParser(void) {}

std::string	FileParser::grapServers(const std::string configText) {
	size_t	pos;

	pos = configText.find("server");
}

// void	FileParser::grapListen(const std::string configText) {
	
// }

// void	FileParser::grapRoot(const std::string configText) {
	
// }

// void	FileParser::grapServerName(const std::string configText) {
	
// }

// void	FileParser::grapErrorPages(const std::string configText) {
	
// }

// void	FileParser::grapClienteBodyBuffer(const std::string configText) {
	
// }

// void	FileParser::grapAllowedMethods(const std::string configText) {
	
// }

// void	FileParser::grapIndex(const std::string configText) {
	
// }

// void	FileParser::grapAutoIndex(const std::string configText) {
	
// }

// void	FileParser::grapLocation(const std::string configText) {
	
// }


// EXCEPTION HANDLING
const char	*FileParser::ExceptionInvalidArguments::what() const throw() {
	return "Exception: invalid arguments in configuration file";
}
