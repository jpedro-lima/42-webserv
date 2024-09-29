/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:40:52 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/29 10:41:48 by joapedr2         ###   ########.fr       */
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
}