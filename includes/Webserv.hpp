/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:03:06 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 16:43:39 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// Colors
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define RESET	"\033[0m"


// CPP Includes
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <string>
# include <limits>
# include <cstdio>

// CPP Containers
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <iterator>
# include <list>
# include <utility>

// My namespaces
# include "Utils.hpp"
# include "FileReader.hpp"


// My Classes
# include "Exceptions.hpp"

typedef	std::vector<std::string>	fileVector;

#endif //WEBSERV_HPP