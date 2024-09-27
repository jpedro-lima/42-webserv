/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:37:43 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/27 10:35:33 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

const char	*Exceptions::ConfigFileErrorException::what() const throw() {
	return "Exception thrown: Configuration file error";
}

const char	*Exceptions::FileNotFoundException::what() const throw() {
	return "Exception thrown: could not open configuration file";
}

const char	*Exceptions::ConfigFileEmptyException::what() const throw() {
	return "Exception thrown: Configuration file is empty";
}

const char	*Exceptions::ExpectedCurlyBracketsAfter::what() const throw() {
	return "Exception thrown: expected '{' after server directive.";
}

const char	*Exceptions::ExpectedCurlyBracketsBefore::what() const throw() {
	return "Exception thrown: Expected '}' at end of directive.";
}

const char	*Exceptions::ExceptionInvalidArguments::what() const throw() {
	return "Exception thrown: the argument for this directive is invalid.";
}

const char	*Exceptions::ExceptionInvalidAllowMethod::what() const throw() {
	return "Exception thrown: the argument in Allow Method is invalid.";
}

const char	*Exceptions::ExceptionInvalidServerName::what() const throw() {
	return "Exception thrown: the argument in ServerName is invalid.";
}

const char	*Exceptions::ExceptionInvalidAutoIndex::what() const throw() {
	return "Exception thrown: the argument in AutoIndex is invalid.";
}


const char	*Exceptions::ExceptionInvalidListenArgs::what() const throw() {
	return "Exception thrown: the argument in Listen is invalid.";
}
