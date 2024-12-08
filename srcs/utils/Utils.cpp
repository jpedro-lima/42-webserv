/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:40:52 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/21 01:45:16 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils {
	bool	isspace(int c) {
		if (c == ' ' || c == '\f' || c == '\n'|| c == '\r'|| c == '\t' || c == '\v' || c == '\0')
			return (true);
		return (false);
	}

	size_t	findMembers(const std::string str, const std::string here) {
		if (str.empty() || here.empty())
			return (std::string::npos);
		
		size_t	pos = 0;
		while ((pos = here.find(str, pos)) != std::string::npos) {
			if (here[pos + str.length()] && Utils::isspace(here[pos + str.length()])
				&& pos > 0 && Utils::isspace(here[pos - 1]))
				return (pos);
			pos++;
		}
		return (std::string::npos);
	}

	bool	isdigit(std::string str) {
		for (size_t i = 0; i < str.length(); i++) {
			if (!std::isdigit(str[i]))
				return (false);
		}
		return (true);
	}

	std::string	&strip(std::string& str, char c) {
		size_t	i;

		if (!str.size())
			return str;
		i = str.size();
		while (i && str[i - 1] == c)
			i--;
		str.resize(i);
		for (i = 0; str[i] == c; i++);
		str = str.substr(i, std::string::npos);
		return str;
	}
	
	std::string	readValue(const std::string line) {
		size_t i;
		std::string	ret;

		i = line.find_first_of(':');
		i = line.find_first_not_of(' ', i + 1);
		if (i != std::string::npos)
			ret.append(line, i, std::string::npos);
		return (strip(ret, ' '));
	}

	std::string	readKey(const std::string line) {
		std::string	ret;

		size_t	i = line.find_first_of(':');
		ret.append(line, 0 , i);
		capitalize(ret);
		return (strip(ret, ' '));
	}
	
	std::string	&capitalize(std::string	&str)
	{

		for (size_t i = 0; i < str.length(); i++)
			str[i] = std::tolower(str[i]);
		str[0] = std::toupper(str[0]);
		size_t	find = 0;
		while((find = str.find_first_of('-', find + 1)) != std::string::npos)
		{
			if (find + 1 < str.size())
			str[find + 1] = std::toupper(str[find + 1]);
		}
		return (str);
	}

	std::string	removeAdjacentSlashes(const std::string &str) {
		std::string	ret;
		bool	lastIsSlash = false;

		for (std::string::size_type i = 0; i < str.length(); i++) {
			if (str[i] == '/') {
				if (!lastIsSlash)
					ret.push_back(str[i]);
				lastIsSlash = true;
			}
			else {
				lastIsSlash = false;
				ret.push_back(str[i]);
			}
		}
		return (ret);
	}

	std::vector<std::string>	split(const std::string& str, char c)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);

		while (std::getline(tokenStream, token, c))
			tokens.push_back(token);
		return tokens;
	}

	int		pathIsFile(const std::string& path) {
		struct stat s;
		if (stat(path.c_str(), &s) == 0 )
		{
			if (s.st_mode & S_IFDIR)
				return 0;
			else if (s.st_mode & S_IFREG)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}

	std::string	toString(size_t n) {
		std::stringstream tmp;
		tmp << n;
		return (tmp.str());
	}
}