/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:03:06 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/30 16:56:40 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#ifndef LOCALHOST
# define LOCALHOST	"127.0.0.1"
#endif //LOCALHOST

// Colors
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define RESET	"\033[0m"

// C Includes
#include <sys/stat.h>
#include <unistd.h>

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

// Structs
typedef struct	s_listen {
	std::string	host;
	int			port;
}				t_listen;

#endif //WEBSERV_HPP