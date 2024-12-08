/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:03:06 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/20 20:48:46 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define LOCALHOST		"127.0.0.1"
# define RECV_SIZE		65536
# define CGI_BUFSIZE	65536

// Colors
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define RESET		"\033[0m"
# define GREY		"\033[38;5;8m"
# define MAGENTA	"\033[35m"	

// C Includes
# include <sys/stat.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <linux/limits.h>
# include <sys/time.h>

// CPP Includes
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <string>
# include <limits>
# include <cstdio>
# include <csignal>
# include <cstring>
# include <algorithm>

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