/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:37:43 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 13:23:24 by joapedr2         ###   ########.fr       */
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

