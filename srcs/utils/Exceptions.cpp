/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:37:43 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 04:17:08 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

const char	*Exceptions::ConfigFileErrorException::what() const throw() {
	return "Exception ConfigFile: Configuration file error";
}

const char	*Exceptions::FileNotFoundException::what() const throw() {
	return "Exception ConfigFile: could not open configuration file";
}

const char	*Exceptions::ConfigFileEmptyException::what() const throw() {
	return "Exception ConfigFile: Configuration file is empty";
}

const char	*Exceptions::ExpectedCurlyBracketsAfter::what() const throw() {
	return "Exception ConfigFile: expected '{' after server directive.";
}

const char	*Exceptions::ExpectedCurlyBracketsBefore::what() const throw() {
	return "Exception ConfigFile: Expected '}' at end of directive.";
}

const char	*Exceptions::ExceptionInvalidArguments::what() const throw() {
	return "Exception ConfigFile: the argument for this directive is invalid.";
}

const char	*Exceptions::ExceptionInvalidAllowMethod::what() const throw() {
	return "Exception ConfigFile: the argument in Allow Method is invalid.";
}

const char	*Exceptions::ExceptionInvalidServerName::what() const throw() {
	return "Exception ConfigFile: the argument in ServerName is invalid.";
}

const char	*Exceptions::ExceptionInvalidAutoIndex::what() const throw() {
	return "Exception ConfigFile: the argument in AutoIndex is invalid.";
}

const char	*Exceptions::ExceptionInvalidListenArgs::what() const throw() {
	return "Exception ConfigFile: the argument in Listen is invalid.";
}

const char	*Exceptions::ExceptionInvalidListenServers::what() const throw() {
	return "Exception ConfigFile: The port and host cannot be shared between servers.";
}

const char	*Exceptions::ExceptionInvalidRootArgs::what() const throw() {
	return "Exception ConfigFile: the argument in Root is invalid.";
}

const char	*Exceptions::ExceptionInvalidErrorPageArgs::what() const throw() {
	return "Exception ConfigFile: the argument in Error Page is invalid.";
}

const char	*Exceptions::ExceptionInvalidClientBodyBufferSize::what() const throw() {
	return "Exception ConfigFile: the argument in Client Body Buffer Size is invalid.";
}

const char	*Exceptions::ExceptionInvalidIndexArgs::what() const throw() {
	return "Exception ConfigFile: the argument in Index is invalid.";
}

const char	*Exceptions::ExceptionInvalidCGIParamArgs::what() const throw() {
	return "Exception ConfigFile: the argument in CGI Param is invalid.";
}

const char	*Exceptions::ExceptionInvalidCGIPassArgs::what() const throw() {
	return "Exception ConfigFile: the argument in CGI Pass is invalid.";
}

const char	*Exceptions::ExceptionInvalidLocationMethod::what() const throw() {
	return "Exception ConfigFile: the Method in Location is invalid.";
}

const char	*Exceptions::ExceptionInvalidServerMethod::what() const throw() {
	return "Exception ConfigFile: the Method in Server is invalid.";
}

const char	*Exceptions::ExceptionServerSocket::what() const throw() {
	return "Exception Server: Could not create Service.";
}

const char	*Exceptions::ExceptionServerBind::what() const throw() {
	return "Exception Server: Could not bind port.";
}

const char	*Exceptions::ExceptionServerListen::what() const throw() {
	return "Exception Server: Could not listen.";
}

const char	*Exceptions::ExceptionServiceServer::what() const throw() {
	return "Exception Serverice: Could not setup Server services.";
}

const char	*Exceptions::FailedReadClientRequest::what() const throw() {
	return "Exception Server: Read Client Request error, closing connection.";
}

const char	*Exceptions::ExceptionRequestParse::what() const throw() {
	return "Exception Request: Request parse failure";
}

const char	*Exceptions::ExceptionSendResponse::what() const throw() {
	return "Exception Request: Error sending the response to the client";
}
