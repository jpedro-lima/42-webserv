/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:07:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 03:15:19 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::~Config(void) {};

Config::Config(std::string configPath) {
	this->_configText = FileReader::readFile(configPath);
	this->_fileVector = FileParser::parse(this->_configText);
}
