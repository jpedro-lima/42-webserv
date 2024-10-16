/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:44 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/11 08:55:16 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Webserv.hpp"

namespace Utils {
	bool	isspace(int c);
	size_t	findMembers(const std::string str, const std::string here);
	bool	isdigit(std::string str);

	std::string	&strip(std::string& str, char c);
	std::string	readValue(const std::string line);
	std::string	readKey(const std::string line);
	std::string	&capitalize(std::string	&str);
	std::string	removeAdjacentSlashes(const std::string &str);
	std::string	toString(size_t n);
	std::vector<std::string>	split(const std::string& str, char c);
	int	pathIsFile(const std::string& path);
}
